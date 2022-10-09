## RLE压缩解压算法

编写一个程序，可以在命令行输入参数，完成指定文件的压缩解压。

命令行参数如下：

```
rle file1 –c(-d) file2
```

第一个参数为可执行程序名称，第二个参数为原始文件名，第三个参数为压缩或解压缩选项，第四个参数为新文件名。

### 算法分析

#### 压缩算法分析

每次从文件读取一定的字节到inputByte中，对这一部分的字节进行解析，每次读取一个字节如果出现**连续三个字节相等**则进行计数，注意总数不能超过**127个**（二进制八位表示范围是**-128到127**）。将总共重复的字节数大小**与0x80按位或**，即取后七位并把第八位置为一，**作为压缩标记**，存入outputByte,再把重复的字节对象存入。若是其他情况则直接写入字节即可。

**代码实现：**

```c
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
```

#### 解压缩算法分析

同样读取字节并对该部分字节解析，每次读取一个字节，**和0x80按位与**，如果有压缩标记，则结果会**等于0x80**（由ASCLL码可以知道，其他没被标记的字节最大也一定小于0x80），那么就再把该字节**与0x7f按位或，即取下二进制后七位数**，也就是重复字节的数量，然后进行读入即可。如果不是标记就直接读入该处字节。

**代码实现：**

```c
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
```

### 程序结构解释

1. 两个文件指针**inputFile**和**outputFile**分别指向初始文件和目标文件。

2. 两个char*型指针**inputByte**和**outputByte**，inputByte负责从inputFile中读取字节，outputByte负责读入处理过后的字节。

3. **Solve**函数进行处理压缩或则解压缩命令并进行文件读取读出，压缩则利用**Encode**函数进行编码，解压缩则利用**Decode**函数进行解码。


### 程序运行结果

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021052800114745.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2FreW5h,size_16,color_FFFFFF,t_70#pic_center)

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021052800114716.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2FreW5h,size_16,color_FFFFFF,t_70#pic_center)

**二进制查看分析：**

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210528190138859.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2FreW5h,size_16,color_FFFFFF,t_70#pic_center)

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021052819023384.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2FreW5h,size_16,color_FFFFFF,t_70#pic_center)

### 后记

完整源码详见我的github项目：[xdu-exp-c](https://github.com/akynazh/xdu-exp-c)。
