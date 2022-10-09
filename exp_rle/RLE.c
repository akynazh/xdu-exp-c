#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void Solve(char* choose, char* inputFileName, char* outputFileName){
	FILE* inputFile = fopen(inputFileName, "rb");
	FILE* outputFile = fopen(outputFileName, "wb");
	if(inputFile == NULL || outputFile == NULL){
		if(inputFile != NULL)	fclose(inputFile);
		if(outputFile != NULL)	fclose(outputFile); 
		printf("can't find the file");
		return;
	}
	unsigned char* inputByte = (unsigned char*)malloc(sizeof(unsigned char)*1024*1024*1024);
	unsigned char* outputByte = (unsigned char*)malloc(sizeof(unsigned char)*1024*1024*1024);
	if(!strcmp(choose, "-c")){
		while(fread(inputByte, sizeof(unsigned char), 1024, inputFile) != 0){
			int size = Encode(inputByte, outputByte);
			fwrite(outputByte, sizeof(unsigned char), size, outputFile);
		} 
	}else{
		while(fread(inputByte, sizeof(unsigned char), 1024, inputFile) != 0){
			int size = Decode(inputByte, outputByte);
			fwrite(outputByte, sizeof(unsigned char), size, outputFile);
		}
	}
	printf("success"); 
	fclose(inputFile);	
	fclose(outputFile);
}
int Encode(unsigned char* inputByte, unsigned char* outputByte){
	unsigned char *in = inputByte, *out = outputByte;
	int left = strlen(inputByte), size = 0;
	while(left > 0){
		if(left < 3){
			out[size++] = *in++;
			left--;
		}else if(in[0] == in[1] && in[1] == in[2]){
			int i = 0, len = 1; 
			while(i < left - 1 && len < 127){//二进制八位表示范围是-128到127，最大数位为127 
				if(in[i] == in[i+1]){
					len++;	i++;
				}else	break;
			}
			out[size++] = len|0x80;//与0x80即二进制10000000按位或 取后七位并把第八位置为一 作为压缩标记 
			out[size++] = *in;
			in += len;	
			left -= len;
		}else{
			out[size++] = *in++;	
			left--;
		}
	}
	return size;
}
int Decode(unsigned char* inputByte, unsigned char* outputByte){
	unsigned char *in = inputByte, *out = outputByte;
	int i = 0, size = 0;
	while(i < strlen(inputByte)){
		//这里按位与运算必须加上括号 否则就变成了in[i]&(0x80==0x80)因为优先级==高于&
		if((in[i] & 0x80) == 0x80){//如果有压缩标记 则与0x80按位与后会等于0x80
			int c = in[i] & 0x7f;//取下后七位数 即重复字节的数量
			i++;
			while(c--)	out[size++] = in[i];
			i++;
		}else{
			out[size++] = in[i++];
		}
	}
	return size;
}
int main(int argc, char *argv[]){
	if(!strcmp(argv[2], "-c") || !strcmp(argv[2], "-d"))	Solve(argv[2], argv[1], argv[3]);
	else	printf("illegal input");
	return 0;
} 
