/*
 * Copyright (c) 2020, Spreadtrum Communications.
 *
 * The above copyright notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * To implement sha256_csum_wd function by calling ahash API in kernel crypto.
 *
 */

#include <crypto/hash.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/gfp.h>
#include <linux/module.h>
#include <linux/scatterlist.h>
#include <linux/string.h>
#include <linux/moduleparam.h>
#include <linux/interrupt.h>

/*
 * Need slab memory for testing (size in number of pages).
 */
#define TVMEMSIZE			4
#define MAX_DIGEST_SIZE		64

static char *tvmem[TVMEMSIZE];

struct crypt_hash_result {
	struct completion completion;
	int err;
};

static void crypt_hash_complete(struct crypto_async_request *req, int err)
{
	struct crypt_hash_result *res = req->data;

	if (err == -EINPROGRESS)
		return;

	res->err = err;
	complete(&res->completion);
}

static void crypto_hash_sg_init(struct scatterlist *sg,
		const char *buf, const size_t buf_len)
{
	int i;
	int cpy_size;
	int round = buf_len / PAGE_SIZE;
	int remainder = buf_len % PAGE_SIZE;

	if (remainder)
		round++;

	if (round > TVMEMSIZE)
		return;

	sg_init_table(sg, round);
	for (i = 0; i < round; i++) {
		if (remainder && (i == (round - 1)))
			cpy_size = remainder;
		else
			cpy_size = PAGE_SIZE;

		memcpy(tvmem[i], buf + i * PAGE_SIZE, cpy_size);
		sg_set_buf(sg + i, tvmem[i], cpy_size);
	}
}

static inline int do_one_ahash_op(struct ahash_request *req, int ret)
{
	if (ret == -EINPROGRESS || ret == -EBUSY) {
		struct crypt_hash_result *tr = req->base.data;

		wait_for_completion(&tr->completion);
		reinit_completion(&tr->completion);
		ret = tr->err;
	}
	return ret;
}

void sprd_crypt_hash(const char *algo, const char *data,
		const unsigned int len, char *digest, unsigned int *digest_size)
{
	struct scatterlist sg[TVMEMSIZE];
	struct crypt_hash_result cresult;
	struct ahash_request *req = NULL;
	struct crypto_ahash *tfm = NULL;
	char *output = NULL;
	int i, round, ret;
	int remainder;
	int already_update = 0;
	int bytes_per_update = 0;

	if ((algo == NULL)   || (data == NULL) ||
		(digest == NULL) || (digest_size == NULL)) {
		pr_err("Parameter error  %s: %d\n",
		       __func__, __LINE__);
		return;
	}

	tfm = crypto_alloc_ahash(algo, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(tfm)) {
		pr_err("failed to load transform for %s: %ld\n",
		       algo, PTR_ERR(tfm));
		return;
	}

	if (crypto_ahash_digestsize(tfm) > MAX_DIGEST_SIZE) {
		pr_err("digestsize(%u) > %d\n", crypto_ahash_digestsize(tfm),
		       MAX_DIGEST_SIZE);
		goto out;
	}

	req = ahash_request_alloc(tfm, GFP_KERNEL);
	if (!req) {
		pr_err("ahash request allocation failure\n");
		goto out;
	}

	init_completion(&cresult.completion);
	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypt_hash_complete, &cresult);

	output = kmalloc(MAX_DIGEST_SIZE, GFP_KERNEL);
	if (!output)
		goto out_nomem;

	round = len / (TVMEMSIZE * PAGE_SIZE);
	remainder = len % (TVMEMSIZE * PAGE_SIZE);
	if (remainder)
		round++;

	ret = do_one_ahash_op(req, crypto_ahash_init(req));
	if (ret)
		goto ahash_op_err;

	for (i = 0; i < round; i++) {
		bytes_per_update = ((remainder && (i == round - 1)) ?
							remainder : (TVMEMSIZE * PAGE_SIZE));
		crypto_hash_sg_init(sg, data + already_update, bytes_per_update);
		ahash_request_set_crypt(req, sg, output, bytes_per_update);

		ret = do_one_ahash_op(req, crypto_ahash_update(req));
		if (ret)
			goto ahash_op_err;
		already_update = already_update + bytes_per_update;
	}

	ret = do_one_ahash_op(req, crypto_ahash_final(req));
	if (ret)
		goto ahash_op_err;

	*digest_size = crypto_ahash_digestsize(tfm);
	memcpy(digest, output, *digest_size);

ahash_op_err:
	kfree(output);

out_nomem:
	ahash_request_free(req);

out:
	crypto_free_ahash(tfm);
}

void sha256_csum_wd(const unsigned char *input, unsigned int ilen,
		unsigned char *output, unsigned int chunk_sz)
{
	unsigned int digest_size = 0;

	if (input == NULL || ilen == 0 || output == NULL) {
		pr_err("%s:%d: Parameter error\n", __func__, __LINE__);
		return;
	}

	sprd_crypt_hash("sha256", input, ilen,
			output,  &digest_size);
}

static int __init crypt_hash_mod_init(void)
{
	int err = 0;
	int i;

	for (i = 0; i < TVMEMSIZE; i++) {
		tvmem[i] = (void *)__get_free_page(GFP_KERNEL);
		if (!tvmem[i])
			goto err_free_tv;
	}

	return err;

err_free_tv:
	for (i = 0; i < TVMEMSIZE && tvmem[i]; i++)
		free_page((unsigned long)tvmem[i]);
	return -ENOMEM;
}

/*
 * If an init function is provided, an exit function must also be provided
 * to allow module unload.
 */
static void __exit crypt_hash_mod_fini(void)
{
	int i;

	for (i = 0; i < TVMEMSIZE && tvmem[i]; i++)
		free_page((unsigned long)tvmem[i]);
}

module_init(crypt_hash_mod_init);
module_exit(crypt_hash_mod_fini);
