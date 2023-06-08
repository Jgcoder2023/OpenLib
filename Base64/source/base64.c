/*base64.c*/  
#include "base64.h"  

//����base64�����  
static uchar base64_table[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static uint table[]={0,0,0,0,0,0,0,0,0,0,0,0,
    		 0,0,0,0,0,0,0,0,0,0,0,0,
    		 0,0,0,0,0,0,0,0,0,0,0,0,
    		 0,0,0,0,0,0,0,62,0,0,0,
    		 63,52,53,54,55,56,57,58,
    		 59,60,61,0,0,0,0,0,0,0,0,
    		 1,2,3,4,5,6,7,8,9,10,11,12,
    		 13,14,15,16,17,18,19,20,21,
    		 22,23,24,25,0,0,0,0,0,0,26,
    		 27,28,29,30,31,32,33,34,35,
    		 36,37,38,39,40,41,42,43,44,
    		 45,46,47,48,49,50,51};

			 
err base64_encode(char *str,char* ReStr){  
    ulong len;  
    ulong str_len;  
    uint i,j;  

	//���㾭��base64�������ַ�������  
    str_len=strlen(str);
	if(str_len == 0){
		return fail;
	}
	
    if(str_len % 3 == 0){
		len=str_len/3*4;  
	}else{
		len=(str_len/3+1)*4;
	}
	//��3��8λ�ַ�Ϊһ����б���  
    for(i=0,j=0;i<len-2;j+=3,i+=4){  
        ReStr[i]=base64_table[str[j]>>2]; //ȡ����һ���ַ���ǰ6λ���ҳ���Ӧ�Ľ���ַ�  
        ReStr[i+1]=base64_table[(str[j]&0x3)<<4 | (str[j+1]>>4)]; //����һ���ַ��ĺ�λ��ڶ����ַ���ǰ4λ������ϲ��ҵ���Ӧ�Ľ���ַ�  
        ReStr[i+2]=base64_table[(str[j+1]&0xf)<<2 | (str[j+2]>>6)]; //���ڶ����ַ��ĺ�4λ��������ַ���ǰ2λ��ϲ��ҳ���Ӧ�Ľ���ַ�  
        ReStr[i+3]=base64_table[str[j+2]&0x3f]; //ȡ���������ַ��ĺ�6λ���ҳ�����ַ�  
    }
    switch(str_len % 3){  
        case 1:  
            ReStr[i-2]='=';  
            ReStr[i-1]='=';  
            break;  
        case 2:  
            ReStr[i-1]='=';  
            break;  
    }
    return ok;  
}  
  

err base64_decode(char *code,char *ReStr){  
//����base64�����ַ��ҵ���Ӧ��ʮ��������  
    ulong len;  
    uint i,j;  
	//����������ַ�������  
    len=strlen(code);
	if(len == 0){
		return fail;
	}

	//��4���ַ�Ϊһλ���н���  
    for(i=0,j=0;i < len-2;j+=3,i+=4){  
        ReStr[j]=((char)table[code[i]])<<2 | (((char)table[code[i+1]])>>4); //ȡ����һ���ַ���Ӧbase64���ʮ��������ǰ6λ��ڶ����ַ���Ӧbase64���ʮ�������ĺ�2λ�������  
        ReStr[j+1]=(((char)table[code[i+1]])<<4) | (((char)table[code[i+2]])>>2); //ȡ���ڶ����ַ���Ӧbase64���ʮ�������ĺ�4λ��������ַ���Ӧbas464���ʮ�������ĺ�4λ�������  
        ReStr[j+2]=(((char)table[code[i+2]])<<6) | ((char)table[code[i+3]]); //ȡ���������ַ���Ӧbase64���ʮ�������ĺ�2λ���4���ַ��������  
    }  
    return ok;
}  


