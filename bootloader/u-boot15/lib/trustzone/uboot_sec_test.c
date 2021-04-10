/*
 * Copyright (c) 2013-2014, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "uboot_sec_drv.h"

/*
  image 校验、及相关扩展的示例调用流程：
*/
void uboot_sec_test(void){

  uint32_t ret;
  uint32_t funcid;
  uint32_t start_adr;
  uint32_t lenth;

  //1、准备传入参数
  funcid = TEESMC64_SIPCALL_WITH_ARG;
  start_adr = 0x58000000; //image 起始地址；
  lenth = 0x200;          //image 长度；

  struct smc_param64 param;
  param.a0 = funcid;
  param.a1 = start_adr;
  param.a2 = lenth;

  //2、调用SMC
  tee_smc_call64(&param);
/*

  3、op-tee中处理逻辑：

  void tee_entry(struct thread_smc_args *args)
  {
    switch (args->a0) {
    case TEESMC32_CALLS_COUNT:
      tee_entry_get_api_call_count(args);
      break;
      ........
    case TEESMC64_SIPCALL_WITH_ARG:
      tee_verify_img_with_arg(args);
      break;
    default:
      args->a0 = TEESMC_RETURN_UNKNOWN_FUNCTION;
      break;
    }
  }
*/
  //4、获取返回值
  ret = param.a0;

}


