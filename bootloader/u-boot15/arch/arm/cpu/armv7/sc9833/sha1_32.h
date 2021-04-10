
/*
* sha1_32.h
*
* Description:
*
* Please read the file sha1_32.c for more information.
*
*/
#ifndef _SHA1_32_H_
#define _SHA1_32_H_
#define SHA1HashSize 20

#define PUBLIC

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

/*
* This structure will hold context information for the SHA-1
* hashing operation
*/
typedef struct SHA1Context32 {
	unsigned int Intermediate_Hash[5];	/* Message Digest */
	unsigned int Length_Low;	/* Message length in bits */
	unsigned int Length_High;	/* Message length in bits */
	/* Index into message block array */
	unsigned int Message_Block_Index;
	unsigned int W[80];	/* 512-bit message blocks */
} SHA1Context_32;

/*
* Function Prototypes
*/
PUBLIC int SHA1Reset_32(SHA1Context_32 *);
PUBLIC int SHA1Input_32(SHA1Context_32 *, const unsigned int *message, unsigned int len);
PUBLIC int SHA1Result_32(SHA1Context_32 * context, unsigned char *Message_Digest);
#endif
