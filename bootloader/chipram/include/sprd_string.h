#ifndef __SPRD_STRING_H__
#define __SPRD_STRING_H__

int sprd_strcmp(const char * cs,const char * ct);
void * sprd_memset(void * string,int fill,size_t cnt);
void* memset(void* s, int c, size_t n);
void * sprd_memcpy(void *dst, const void *src, size_t cnt);

#endif /*__SPRD_STRING_H__*/
