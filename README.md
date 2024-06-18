# 1.项目（chat）介绍
一个为了练习 C/C++ 的学习项目


## 1.1.编译
```angular2html
rm -rf cmake-build-debug
mkdir cmake-build-debug
cd cmake-build-debug

cmake ..
make
```

## 1.2.运行命令
### 启动服务端
```chat start_server```

### 注册用户
```chat register --name=yunlongwang --password=123456```

### 登陆用户
```chat register --name=yunlongwang --password=123456```

### 群聊｜私聊
```
默认是群发，想转为私聊操作如下：
#zhangsan
再次切换为群发操作如下
#
```

# 2.源码分析
## 2.1.数据编码
```
// 数据编码
D:from:to:rowdata

D：代表消息类型是数据；
from：代表是谁发的；
to：代表是群发，还是私发；
rowdata：用户原始数据；
```