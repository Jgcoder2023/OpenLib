#ifndef Base64_H__
#define Base64_H__

#include <stdlib.h>  
#include <string.h> 

typedef unsigned char uchar;
typedef unsigned int uint; 
typedef unsigned long ulong;
typedef void* any;

//定义错误状态的返回
typedef enum {
	ok = 0,
	fail
}err;


err base64_encode(char *str,char* ReStr);
err base64_decode(char *code,char *ReStr);



#endif

