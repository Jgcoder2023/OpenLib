#include "base64.h"    //引入base64头文件
void main(void){
  //要加密的字符串
  char* str = "123123";
  char enstr[100] = {0};   //定义接受加密后的数组
  char destr[100] = {0};   //定义接受解密后的数组


  //调用加密方法
  //如果返回ok则表示加密成功，否则失败
  if(base64_encode(str,enstr) == ok){
		printf("%s \r\n",enstr);
	}

  //调用解密方法
  //如果返回ok则表示解密成功，否则失败
	if(base64_decode(enstr,destr) == ok){
		printf("%s \r\n",destr);
	}



}