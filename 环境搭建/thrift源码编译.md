#### thrift源码编译

基础环境为centos7.7

```
yum -y install automake libtool flex bison pkgconfig gcc-c++ boost-devel libevent-devel zlib-devel python-devel ruby-devel openssl-devel

unzip thrift-0.9.3.zip 

cd thrift-0.9.3

./bootstrap.sh 

./configure –-prefix=/mnt

./configure –-help

make && make install

thrift --version

编译完成以后查找是否有相应的库

find / -name "libthrift.so"

//此时能够得到so，但是无法等到正确编译结束，缺少boost
g++: error: /usr/lib64/libboost_unit_test_framework.a: No such file or directory
```



- 如果编译安装无法正确结束，安装boost库

  ```
  yum -y install libboost-all-dev
  
  wget http://sourceforge.net/projects/boost/files/boost/1.53.0/boost_1_53_0.tar.gz
  cd boost_1_53_0./bootstrap.sh
  
  sudo ./b2 install  //需要等待一段时间
  
  yum install boost
  
  yum install boost-devel
  
  yum install boost-doc
  ```

  

- 继续thrift的安装编译

  ```
  //执行查找命令，是否能够找到的库文件，先将相应的boost库拷贝过去，然后继续安装，此时能够正常结束
  
  ls /usr/lib64/libboost_unit_test_framework*
  
  make -n | grep libboost_unit_test_framework
  
  ls /usr/local/lib/libboost_unit_test_framework.*
  
  cp /usr/local/lib/libboost_unit_test_framework.a /usr/lib64/
  
  //继续thrift安装
  
  make && make install
  
  find / -name "libthrift.so"
  ```

  





- 参考网址

  https://my.oschina.net/u/1540325/blog/552694

  https://www.cnblogs.com/lawlietfans/p/6309061.html

  https://www.cnblogs.com/lawlietfans/p/6309061.html

  官方网址

  http://thrift.apache.org/docs/install/centos