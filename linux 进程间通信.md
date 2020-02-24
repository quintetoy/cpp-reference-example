##### linux 进程间通信—信号通信---signal

信号（signal）机制是UNIX系统中最为古老的进程间通信机制，很多条件可以产生一个信号。

```
	Q:这两个函数的使用方法，以及各个参数代表的是什么？
	signal(SIGINT, mainExit);
	signal(SIGTSTP, mainExit);
```



```
A:signal(SIGINT,my_func);
```



- 信号的产生

  1、用户按下某些键

  2、使用kill

  3、硬件异常信号

- 信号的类型

  1、SIGHUP:从终端上发出的结束信号

  2、SIGINT：来自键盘的中断信号（ctrl+c）

  3、SIGKILL：该信号结束接受信号的进程

  4、SIGTERM：kill 命令发出的信号

  5、SIGHCHLD：标识子进程停止或结束的信号

  6、SGISTOP：来自键盘（ctrl+z）或调试程序的停止执行的信号



所以最刚开始的问题中后续的函数代表，当信号出现时，执行的操作。

可以忽略，也可以执行系统默认动作（终止进程）