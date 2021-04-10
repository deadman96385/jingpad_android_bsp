#include "sha1_32.h"
PUBLIC int SHA1Reset_32(SHA1Context_32 * context32)
{
	context32->Length_Low = 0;
	context32->Length_High = 0;
	context32->Message_Block_Index = 0;
	context32->Intermediate_Hash[0] = 0x67452301;
	context32->Intermediate_Hash[1] = 0xEFCDAB89;
	context32->Intermediate_Hash[2] = 0x98BADCFE;
	context32->Intermediate_Hash[3] = 0x10325476;
	context32->Intermediate_Hash[4] = 0xC3D2E1F0;
	return 0;
}

#define SHA1CircularShift(bits,word) (((word) << (bits)) | ((word) >> (32-(bits))))
#define F0_19(A,B,C,D,E,Wt,Kn) \
		E += SHA1CircularShift(5,A) + ((B & C) | ((~B) & D));\
		E += Wt + Kn; \
		B = SHA1CircularShift(30,B);
#define F20_39(A,B,C,D,E,Wt,Kn) \
		E += SHA1CircularShift(5,A) + (B ^ C ^ D);\
		E += Wt + Kn; \
		B = SHA1CircularShift(30,B);
#define F40_59(A,B,C,D,E,Wt,Kn) \
		E += SHA1CircularShift(5,A) + ((B & C) | (B & D) | (C & D));\
		E += Wt + Kn; \
		B = SHA1CircularShift(30,B);
#define F60_79(A,B,C,D,E,Wt,Kn) \
		E += SHA1CircularShift(5,A) + (B ^ C ^ D);\
		E += Wt + Kn; \
		B = SHA1CircularShift(30,B);

int SHA1ProcessMessageBlock_32(SHA1Context_32 * context)
{
	const unsigned int K[] = {	/* Constants defined in SHA-1 */
		0x5A827999,
		0x6ED9EBA1,
		0x8F1BBCDC,
		0xCA62C1D6
	};
	int t;			/* Loop counter */
	unsigned int A, B, C, D, E;	/* Word buffers */
	unsigned int *W;
	unsigned int *H;
	W = context->W;
	H = context->Intermediate_Hash;
	/*
	 * Initialize the first 16 words in the array W
	 */
	for (t = 16; t < 80; t++) {
		context->W[t] = SHA1CircularShift(1, context->W[t - 3] ^ context->W[t - 8] ^ context->W[t - 14] ^ context->W[t - 16]);
	}
	A = H[0];
	B = H[1];
	C = H[2];
	D = H[3];
	E = H[4];

	//F0_19(A,B,C,D,E,context->W[0],K[0])
	F0_19(A, B, C, D, E, W[0], K[0])
	    F0_19(E, A, B, C, D, W[1], K[0])
	    F0_19(D, E, A, B, C, W[2], K[0])
	    F0_19(C, D, E, A, B, W[3], K[0])
	    F0_19(B, C, D, E, A, W[4], K[0])
	    F0_19(A, B, C, D, E, W[5], K[0])
	    F0_19(E, A, B, C, D, W[6], K[0])
	    F0_19(D, E, A, B, C, W[7], K[0])
	    F0_19(C, D, E, A, B, W[8], K[0])
	    F0_19(B, C, D, E, A, W[9], K[0])
	    F0_19(A, B, C, D, E, W[10], K[0])
	    F0_19(E, A, B, C, D, W[11], K[0])
	    F0_19(D, E, A, B, C, W[12], K[0])
	    F0_19(C, D, E, A, B, W[13], K[0])
	    F0_19(B, C, D, E, A, W[14], K[0])
	    F0_19(A, B, C, D, E, W[15], K[0])
	    F0_19(E, A, B, C, D, W[16], K[0])
	    F0_19(D, E, A, B, C, W[17], K[0])
	    F0_19(C, D, E, A, B, W[18], K[0])
	    F0_19(B, C, D, E, A, W[19], K[0])
	    F20_39(A, B, C, D, E, W[20], K[1])
	    F20_39(E, A, B, C, D, W[21], K[1])
	    F20_39(D, E, A, B, C, W[22], K[1])
	    F20_39(C, D, E, A, B, W[23], K[1])
	    F20_39(B, C, D, E, A, W[24], K[1])
	    F20_39(A, B, C, D, E, W[25], K[1])
	    F20_39(E, A, B, C, D, W[26], K[1])
	    F20_39(D, E, A, B, C, W[27], K[1])
	    F20_39(C, D, E, A, B, W[28], K[1])
	    F20_39(B, C, D, E, A, W[29], K[1])
	    F20_39(A, B, C, D, E, W[30], K[1])
	    F20_39(E, A, B, C, D, W[31], K[1])
	    F20_39(D, E, A, B, C, W[32], K[1])
	    F20_39(C, D, E, A, B, W[33], K[1])
	    F20_39(B, C, D, E, A, W[34], K[1])
	    F20_39(A, B, C, D, E, W[35], K[1])
	    F20_39(E, A, B, C, D, W[36], K[1])
	    F20_39(D, E, A, B, C, W[37], K[1])
	    F20_39(C, D, E, A, B, W[38], K[1])
	    F20_39(B, C, D, E, A, W[39], K[1])
	    F40_59(A, B, C, D, E, W[40], K[2])
	    F40_59(E, A, B, C, D, W[41], K[2])
	    F40_59(D, E, A, B, C, W[42], K[2])
	    F40_59(C, D, E, A, B, W[43], K[2])
	    F40_59(B, C, D, E, A, W[44], K[2])
	    F40_59(A, B, C, D, E, W[45], K[2])
	    F40_59(E, A, B, C, D, W[46], K[2])
	    F40_59(D, E, A, B, C, W[47], K[2])
	    F40_59(C, D, E, A, B, W[48], K[2])
	    F40_59(B, C, D, E, A, W[49], K[2])
	    F40_59(A, B, C, D, E, W[50], K[2])
	    F40_59(E, A, B, C, D, W[51], K[2])
	    F40_59(D, E, A, B, C, W[52], K[2])
	    F40_59(C, D, E, A, B, W[53], K[2])
	    F40_59(B, C, D, E, A, W[54], K[2])
	    F40_59(A, B, C, D, E, W[55], K[2])
	    F40_59(E, A, B, C, D, W[56], K[2])
	    F40_59(D, E, A, B, C, W[57], K[2])
	    F40_59(C, D, E, A, B, W[58], K[2])
	    F40_59(B, C, D, E, A, W[59], K[2])
	    F60_79(A, B, C, D, E, W[60], K[3])
	    F60_79(E, A, B, C, D, W[61], K[3])
	    F60_79(D, E, A, B, C, W[62], K[3])
	    F60_79(C, D, E, A, B, W[63], K[3])
	    F60_79(B, C, D, E, A, W[64], K[3])
	    F60_79(A, B, C, D, E, W[65], K[3])
	    F60_79(E, A, B, C, D, W[66], K[3])
	    F60_79(D, E, A, B, C, W[67], K[3])
	    F60_79(C, D, E, A, B, W[68], K[3])
	    F60_79(B, C, D, E, A, W[69], K[3])
	    F60_79(A, B, C, D, E, W[70], K[3])
	    F60_79(E, A, B, C, D, W[71], K[3])
	    F60_79(D, E, A, B, C, W[72], K[3])
	    F60_79(C, D, E, A, B, W[73], K[3])
	    F60_79(B, C, D, E, A, W[74], K[3])
	    F60_79(A, B, C, D, E, W[75], K[3])
	    F60_79(E, A, B, C, D, W[76], K[3]) F60_79(D, E, A, B, C, W[77], K[3]) F60_79(C, D, E, A, B, W[78], K[3]) F60_79(B, C, D, E, A, W[79], K[3]) H[0] +=
	    A;
	H[1] += B;
	H[2] += C;
	H[3] += D;
	H[4] += E;
	return 0;
}

PUBLIC int SHA1Input_32(SHA1Context_32 * context, const unsigned int *message_array, unsigned int length)
{
	while (length--) {
		context->W[context->Message_Block_Index++] = *message_array;
		message_array++;
		context->Length_Low += 32;
		if (context->Length_Low == 0) {
			context->Length_High++;
		}
		if (context->Message_Block_Index == 16) {
			SHA1ProcessMessageBlock_32(context);
			context->Message_Block_Index = 0;
		}
	}
	return 0;
}

int SHA1PadMessage_32(SHA1Context_32 * context)
{
	/*
	 * Check to see if the current message block is too small to hold
	 * the initial padding bits and length. If so, we will pad the
	 * block, process it, and then continue padding into a second
	 * block.
	 */
	unsigned int i, cnt = context->Message_Block_Index;
	context->W[cnt++] = 0x80000000;
	for (i = cnt; i < 16; i++) {
		context->W[i] = 0;
	}

	if (cnt > 14) {
		SHA1ProcessMessageBlock_32(context);
		for (i = 0; i < 14; i++) {
			context->W[i] = 0;
		}
	}
	/*
	 * Store the message length as the last 8 octets
	 */
	context->W[14] = context->Length_High;
	context->W[15] = context->Length_Low;
	SHA1ProcessMessageBlock_32(context);
	return 0;
}

PUBLIC int SHA1Result_32(SHA1Context_32 * context, unsigned char *Message_Digest)
{
	int i;
	uint32_t *ptr;
	ptr = (uint32_t *) context->W;
	SHA1PadMessage_32(context);
	for (i = 0; i < 16; ++i) {
		/* message may be sensitive, clear it out */
		*(ptr + i) = 0;
	}
	context->Length_Low = 0;	/* and clear length */
	context->Length_High = 0;
	for (i = 0; i < SHA1HashSize; ++i) {
		Message_Digest[i] = context->Intermediate_Hash[i >> 2] >> 8 * (3 - (i & 0x03));
	}
	return 0;
}
