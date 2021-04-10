#ifndef SCI_TYPES_H
#define SCI_TYPES_H


/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif

    /* ------------------------------------------------------------------------
    ** Constants
    ** ------------------------------------------------------------------------ */

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

#define TRUE   1   /* Boolean true value. */
#define FALSE  0   /* Boolean false value. */

#ifndef NULL
#define NULL  0
#endif

    /* -----------------------------------------------------------------------
    ** Standard Types
    ** ----------------------------------------------------------------------- */
    typedef unsigned char		BOOLEAN;
    typedef unsigned char		uint8;
    typedef unsigned short		uint16;
    typedef unsigned long int	uint32;
    typedef unsigned long int 	uint64;
    typedef unsigned int		uint;

    typedef signed char			int8;
    typedef signed short		int16;
    typedef signed long int		int32;

typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;

typedef unsigned long ulong;
typedef unsigned int size_t;

#define	LOCAL		static
#define PUBLIC
#endif