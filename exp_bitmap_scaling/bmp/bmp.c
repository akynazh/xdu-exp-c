#include<stdio.h>
#include<malloc.h>
#include<string.h>
#pragma pack(1)	// 让结构体中各成员按1字节对齐,方便后序文件读写操作 

//BMP四大件: 1.文件头 2.消息头 3.调色板 4.位图数据 

//文件头
typedef struct tagBITMAPFILEHEADER {
	//unsigned short bfType;	  // 保存图片类型，读取时需要先注释掉，文本标识符只能单独进行读写
    unsigned int   bfSize;        // 文件大小
    unsigned short bfReserved1;   // 保留，设置为0
    unsigned short bfReserved2;   // 保留，设置为0
    unsigned int   bfOffBits;     // 从文件头到实际的图像数据之间的字节的偏移量
}BITMAPFILEHEADER;
//信息头
typedef struct tagBITMAPINFOHEADER {
    unsigned int    biSize;          // 此结构体的大小
    unsigned int    biWidth;         // 图像的宽
    unsigned int    biHeight;        // 图像的高
    unsigned short  biPlanes;        // 颜色平面数 恒为1
    unsigned short  biBitCount;      // 一像素所占的位数 一般为24
    unsigned int    biCompression;   // 说明图象数据压缩的类型，0为不压缩
    unsigned int    biSizeImage;     // 图像大小, 值等于上面文件头结构中bfSize-bfOffBits
    int             biXPelsPerMeter; // 说明水平分辨率，用像素/米表示 一般为0 
    int             biYPelsPerMeter; // 说明垂直分辨率，用像素/米表示 一般为0 
    unsigned int    biClrUsed;       // 说明位图实际使用的彩色表中的颜色索引数（设为0的话，则说明使用所有调色板项）
    unsigned int    biClrImportant;  // 说明对图象显示有重要影响的颜色索引的数目 如果是0表示都重要
}BITMAPINFOHEADER;
//调色板[共256(==2^8)种索引颜色，8位以上的可以没有调色板]
struct PixelInfo {
    unsigned char rgbBlue;     //该颜色的蓝色分量  (值范围为0-255)
    unsigned char rgbGreen;    //该颜色的绿色分量  (值范围为0-255)
    unsigned char rgbRed;      //该颜色的红色分量  (值范围为0-255)
    unsigned char rgbReserved; // 保留，必须为0
};
BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;

//显示bmp图片文件头内容 
void showBmpHead(BITMAPFILEHEADER pBmpHead)
{  
	//printf("文件标识符：%x\n", fileHeader.bfType);
	printf("BMP文件大小：%dkb\n", fileHeader.bfSize);
	printf("保留字必须为0：%d\n", fileHeader.bfReserved1);
	printf("保留字必须为0：%d\n", fileHeader.bfReserved2);
	printf("实际位图数据的偏移字节数: %d\n", fileHeader.bfOffBits);
}
//显示bmp图片位图信息头内容 
void showBmpInfoHead(BITMAPINFOHEADER pBmpinfoHead)
{
	printf("位图信息头:\n");
	printf("信息头的大小:%d\n", infoHeader.biSize);
	printf("位图宽度:%d\n", infoHeader.biWidth);
	printf("位图高度:%d\n", infoHeader.biHeight);
	printf("图像的位面数(位面数是调色板的数量,默认为1个调色板):%d\n", infoHeader.biPlanes);
	printf("每个像素的位数:%d\n", infoHeader.biBitCount);
	printf("压缩方式:%d\n", infoHeader.biCompression);
	printf("图像的大小:%d\n", infoHeader.biSizeImage);
	printf("水平方向分辨率:%d\n", infoHeader.biXPelsPerMeter);
	printf("垂直方向分辨率:%d\n", infoHeader.biYPelsPerMeter);
	printf("使用的颜色数:%d\n", infoHeader.biClrUsed);
	printf("重要颜色数:%d\n", infoHeader.biClrImportant);
}
int main(int agrc, char *argv[]) {
	FILE* fp;
	unsigned short fileType;
	fp = fopen("zh.bmp", "rb");
	if (fp == NULL) {
		printf("打开图片'img.bmp'失败!\n");
		return -1;
	}
	fread(&fileType, sizeof(unsigned short), 1, fp);
	//42 4d : 4d42 : 19778
	//e6 1e 04 00 : 00041ee6 : 270054字节 
	if (fileType == 0x4d42)//bfType,图片的类型,必须是BMP, 0x4d42(即十进制的19778) 
	{
		printf("文件类型标识正确!");
		printf("\n文件标识符：%x\n", fileType);
		fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
		showBmpHead(fileHeader);
		fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
		showBmpInfoHead(infoHeader);
		fclose(fp); 
	}
	return 0;
}
