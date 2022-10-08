## 简单文件数据库-模拟图书馆管理系统

### 题目简介

涉及知识点：文件读写、内存管理、结构体定义、基本数据结构、高级格式化输入输出

要求：编写一个程序模拟图书管理系统。

用户分为**管理员和读者**两类，分别显示不同文本格式菜单，通过菜单项对应数字进行选择。

读者菜单包括**借书、还书、查询**等功能。

管理员菜单包括图书和读者信息**录入、修改和删除**。

图书信息至少应包括：**编号、书名、数量**。

读者信息至少应包括：**编号、姓名、所借图书**。

可根据图书名称或编号进行图书信息查询，可查询某本书现在被哪些读者借走。

命令行参数如下：

```
Libsim –a(-u) xxxx
```

第一个参数为可执行程序名称；

第二个参数为用户身份，-a表示管理员，-u表示读者；

第三个参数为用户名

### 程序解析

#### 几个函数说明

**1.展示读者和图书信息**

```c
void ShowBook(char* bname);
void ShowReader(char* rname);
```

**2.图书借阅和归还**

```c
void BookLend(char *rname, char *bname);
void BookReturn(char *rname, char* bname);
```

**3.图书和读者信息增删**

```c
void AddBook(char* bname);
void DelBook(char* bname);
void AddReader(char* rname, char* reroot);							
void DelReader(char* rname);
```

**4.读取读者，管理员和图书信息**

```c
void ReadBooksInfo();
void ReadReadersInfo();
void ReadAdministratorsInfo();
```

**5.更新读者，管理员和图书信息**

```c
void UpdateBorrowerList();
void UpdateBorrowedBookList();
void UpdateBookleft();
void UpdateBooks();
void UpdateReaders();
void UpdateAdministrators();
void UpdateReroots();
void UpdateAdroots();
```

### 文件数据库信息编写规则

```
每个文件以end作为结尾
而null表示该书或读者已经被删除

books.txt：
每行一本书，第一行的书编号为1
readers.txt:
每行一个读者姓名，第一行的读者编号为1
administrators.txt:
每行一个管理员姓名，第管理员一行的读者编号为1

books'borrowers.txt:
每行若干个人名，第一行对应编号为1的书的借阅人
borrowers'books.txt:
每行若干个书名，第一行对应编号为1的人的在借书

reroots.txt:
每行一个密码，第一行对应编号为1的读者的密码
adroots.txt
每行一个密码，第一行对应编号为1的管理员的密码
```

### 后记

完整源码详见我的github项目：[xdu-exp-c](https://github.com/akynazh/xdu-exp-c)。
