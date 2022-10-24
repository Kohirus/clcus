#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <unordered_map>
#include <functional>
#include <muduo/net/TcpConnection.h>
#include "json.hpp"

using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

using MsgHandler = std::function<void(const TcpConnectionPtr& conn, json& js, Timestamp)>;

class ChatService {
public:
    // 获取单例对象
    static ChatService* instance();
    // 处理登录业务
    void login(const TcpConnectionPtr& conn, json& js, Timestamp time);
    // 处理注册业务
    void reg(const TcpConnectionPtr& conn, json& js, Timestamp time);
    // 获取消息对应的处理器
    MsgHandler getHandler(int msgid);

private:
    ChatService();

private:
    // 存储消息ID和其对应的业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;
};

#endif // !CHATSERVICE_H
