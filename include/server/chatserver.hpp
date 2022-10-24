#ifndef CHARSERVER_H
#define CHARSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

class ChatServer {
public:
    // 初始化聊天服务器对象
    ChatServer(EventLoop* loop, const InetAddress& listenAddr, const string& nameArg);
    // 启动服务
    void start();

private:
    // 连接相关信息的回调函数
    void onConnection(const TcpConnectionPtr&);

    // 读写事件相关信息的回调函数
    void onMessage(const TcpConnectionPtr&, Buffer*, Timestamp);

private:
    TcpServer  _server;
    EventLoop* _loop; // 事件循环
};

#endif // !CHARSERVER_H
