# C语言

## 关于这篇文章

这篇文章不是教程，是我的笔记。所以不能希望这里没有任何错误并且具有权威性。我也不保证这篇文章能让任何人轻松愉悦地学习到关于C语言的知识。因此，关于如何利用这篇文章、以何种方式阅读这篇文章、利用文章的哪些部分等等，这些应该由读者自己决定。

## 笔记内容

### P1，C语言源程序文件的编译和执行

C语言是一种编程语言。与其它高级编程语言不同的地方是，它可以通过指针直接操作内存数据。作为一种古老的编程语言，不支持OOP、语法复杂以及内存操作错误会导致程序崩溃使得它虽然性能优秀但是应用场合有限。

这种硬件相关、不支持面向对象的特性使得C语言不适合作为编程学习的入门语言。如果把C作为编程入门语言，那就不得不花时间学习很多硬件相关的编程操作，这跟现代软件工程的OOP和设计原理其实没有联系。这可以解释为何`python`这种弱类型硬件无关的解释型语言逐渐成为编程入门课程的教学语言。

在Linux系统上，编译C语言的工具是GCC。GCC可以在各Linux发行版的包管理器中下载安装。

C语言的写法示例：

    #include <stdio.h>

    int main()
    {
        printf("Hi.\n");
        return 0;
    }

第一行，`#include <stdio.h>`放在文件的开头，用来包含一些函数的定义，使得下文可以正确调用。`printf`就是在`stdio.h`中定义的。`main`函数是C语言命令程序执行的入口，这意味着所有逻辑都从`main`开始执行。

将C语言源代码编译成可执行文件的方式是：

    gcc main.c

这会生成一个`a.out`可执行文件。执行`a.out`：

    ./a.out

`a.out`是默认的文件名，可以指定别的文件名作为输出：

    gcc main.c -o another_name

这里`main.c`是源代码的文件名。

### P2，C语言中的变量

#### 整数

C语言中整数类型定义比较复杂。`char`和`int`都是整数，只是它们长度不同。

    char ch = 'X';
    int num = 10;
    printf("char:%d,int:%d\n", sizeof ch, sizeof num);

程序输出：

    char:1,int:4

`char`定义的整数1字节，8位，`int`是4字节，64位（这个取决于电脑系统是32位还是64位）。抛去历史因素不谈，这些整形长度的差距仅仅是内存占用不同和因此导致的取值范围不同而已。

#### 浮点数

`float`和`double`组成常用的两种浮点数。与整数的差别是它们是用来保存带有小数的数。当然它们长度也不同。

    float:4,double:8

在我电脑上`float`是4字节，`double`是8字节。

#### 指针

变量类型和变量名称之间加个`*`就可以定义一个相应的类型的指针了。什么是指针呢？变量是存储在内存里面的，而程序对变量进行操作实际上就是去内存里面对相应的地址里面的值进行操作。指针保存的就是内存的地址。

    #include <stdio.h>
    
    int main()
    {
        char a;
        char * b;
        printf("sizeof a:%d, sizeof b:%d\n", sizeof a, sizeof b);
        return 0;
    }

我电脑是64位的，所以内存地址是8字节。输出结果是：

    sizeof a:1, sizeof b:8

无论类型是`int`或者`char`，它们的指针长度都是一样的，具体长度跟电脑位数有关。

由于每一个变量都是在内存里面的，所以每一个变量必然是在一个内存地址内。取地址符`&`可以获得任意一个变量在内存中的地址。

指针是C语言的一种单独的数据类型，虽然在定义的时候总是需要指定一个`char`或者`int`之类的类型名称，但是它们跟`int`或者`char`并没有绝对的联系。`double`与`int`在我电脑上具有相同的长度，完全可以用强制类型转换的方法将`double`的指针转换为`int`的指针，然后赋给一个通过`int *`定义的指针。

指针内的值可以通过`*`取得。C语言`*`的用法有些复杂，可以表示乘法运算，也可以用来定义指针，也可以同来取得指针内的真实值。

    #include <stdio.h>
    
    int main()
    {
        int c = 2333; // c是一个整型的变量
        int* d;       // d是一个指针，int* 限制这个指针指向的值必须是整型变量
        d = &c;       // 取c的地址，赋给d
        printf("c=%d,d=%d\n", c, d);
        printf("*d=%d\n", *d); // 通过*号取指针d内的值
        return 0;
    }

程序输出

    c=2333,d=-1460401468
    *d=2333

##### 指向指针的指针

指针是保存内存地址的变量，这个变量本身也在内存里面保存。所以指针也具有一个内存的地址。那么问题来了，能不能定义一个指针用来保存另一个指针的地址呢？

    #include <stdio.h>
    
    int main()
    {
        int number = 233;
        int* first_pointer; // 指向int类型的指针
        int** second_pointer; // 指向int*类型的指针
    
        first_pointer = &number;
        second_pointer = &first_pointer;
    
        printf("second_pointer = %d\n", second_pointer);
        printf("*second_pointer = %d\n", *second_pointer);
        printf("**second_pointer = %d\n", **second_pointer);
    
        return 0;
    }

程序输出：

    second_pointer = 1760140440
    *second_pointer = 1760140452
    **second_pointer = 233

#### 字符串

C语言并没有专门的字符串类型。`char`是一个长度为1字节的整数。

#### 数组

C语言的数组是一个单独的数据类型，有它自己的特性。使用`sizeof`可以拿到数组占据的内存大小，其次数组在内存的分布又是连续的。对于一个定义好的数组，`a[20]`，在使用的使用通过键来取得操作对应元素的值：

    #include <stdio.h>
    
    int main()
    {
        int a[20];
        int i;
    
        printf("sizeof a:%d\n", sizeof a);
    
        for (i = 0; i < 20; i++) {
            a[i] = i;
        }
        for (i = 0; i < 20; i++) {
            printf("%d ", a[i]);
        }
    
        printf("\n");
        return 0;
    }

输出：

    sizeof a:80
    0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19

## 基本变量类型的小结

请参考 [Types.md](Types.md "变量类型")