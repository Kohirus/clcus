#include "chatservice.hpp"
#include "public.hpp"
#include <muduo/base/Logging.h>

using namespace std;
using namespace muduo;

ChatService* ChatService::instance() {
    static ChatService service;
    return &service;
}

ChatService::ChatService() {
    // 用户基本业务管理相关事件的回调注册
    _msgHandlerMap.insert({ LOG_MSG, std::bind(&ChatService::login, this, _1, _2, _3) });
    _msgHandlerMap.insert({ REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3) });
}

void ChatService::login(const TcpConnectionPtr& conn, json& js, Timestamp time) {
    LOG_INFO << "do login service!!!";
}

void ChatService::reg(const TcpConnectionPtr& conn, json& js, Timestamp time) {
    LOG_INFO << "do register service!!!";
}

MsgHandler ChatService::getHandler(int msgid) {
    // 记录错误日志 msgid 没有对应的事件处理器
    auto it = _msgHandlerMap.find(msgid);
    if (it == _msgHandlerMap.end()) {
        // 返回一个默认的处理器 空操作
        return [=](const TcpConnectionPtr& conn, json& js, Timestamp) {
            LOG_ERROR << "msgid: " << msgid << " can not find handler!";
        };
    } else {
        return _msgHandlerMap[msgid];
    }
}
