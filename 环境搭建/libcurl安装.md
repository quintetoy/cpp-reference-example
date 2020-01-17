##### libcurl安装





首先从官网下载安装包https://curl.haxx.se/download.html，并解压

```
wget http://curl.haxx.se/download/curl-7.20.0.tar.gz
tar -xvf curl-7.20.0.tar.gz
sudo ./configure
sudo make
sudo make install
```



测试是否安装成功

```
直接输入curl
curl
如果安装成功会出现
curl: try 'curl --help' or 'curl --manual' for more information
如果该命令不存在，则执行以下命令
export PATH=$PATH:/usr/local/curl/bin
```



检查库和头文件

```
[root@server222 curl-7.20.0]# curl-config --cflags
-I/home/***/anaconda3/include
[root@server222 curl-7.20.0]# curl-config --libs
-L/home/***/anaconda3/lib -lcurl
```



参考网站<https://www.cnblogs.com/lantingg/p/8872314.html>



简单的使用

curl发送post请求

```
curl -H "Content-Type:application/json"
			-X POST
			-d '{"user_id":abc,"coin":123,"success":1,"msg":"ok"}' 		   	"http://192.168.2.3:8001:test"
```

| 参数 | 内容     |
| ---- | -------- |
| -H   | 请求头   |
| -d   | POST内容 |
| -X   | 请求协议 |



curl发送get请求

```
curl http://127.0.0.1:8080/login?admin&passwd=12345678

//或者这种形式
curl -X GET http://192.168.40.253:8002/abcd
```



