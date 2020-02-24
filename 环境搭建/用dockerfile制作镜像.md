#### 用dockerfile制作镜像

```
docker run --name=rtsp2rtmp0 --privileged -itd -p 9330-9332:9330-9332 ubuntu:latest /bin/bash
docker exec -it rtsp2rtmp0 /bin/bash

apt update

apt install build-essential vim  libpcre3 libpcre3-dev zlib1g-dev libssl-dev wget curl

mkdir /app
cd /app

wget http://nginx.org/download/nginx-1.17.7.tar.gz 
wget https://github.com/arut/nginx-rtmp-module/archive/master.zip
tar -zxvf nginx-1.17.7.tar.gz

unzip master.zip

mv nginx-rtmp-module-master nginx-rtmp-module

cd nginx-1.17.7

./configure --with-http_ssl_module --add-module=../nginx-rtmp-module

make -j32 sudo make install

cp -r ../nginx-rtmp-module /usr/local/nginx/

cd ..

mv nginx-1.17.7 /usr/local/nginx

wget https://raw.github.com/JasonGiedymin/nginx-init-ubuntu/master/nginx -O /etc/init.d/nginx

chmod +x /etc/init.d/nginx

chkconfig --add /etc/init.d/nginx //不成功

vim /usr/local/nginx/conf/nginx.conf


//这几个暂时不需要
   42  apt install openssl
   43  apt install openssl-dev
   44  apt install libopenssl-dev
   45  apt install libssl-dev
   
   
   

docker run --name=rtsp2rtmp0 --privileged -itd -p 9330-9332:9330-9332 ubuntu:latest /bin/bash
docker exec -it rtsp2rtmp0 /bin/bash

service nginx start


//修改http的映射接口
vim /usr/local/nginx/conf/nginx.conf
//修改监听（转发接口）的接口和服务接口（rtmp）

改配置
RtmpServerNum=1
RtmpUrl1=127.0.0.1:9331 控制（接rtmp）
RtmpControlUrl1=127.0.0.1:9330 转发接口


//开始运行
nohup ./monitor ./rtsp2rtmp &
```





