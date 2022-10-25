#include "chatservice.hpp"
#include "public.hpp"
#include <muduo/base/Logging.h>
#include <mutex>
#include "public.hpp"

using namespace std;
using namespace muduo;

ChatService* ChatService::instance() {
    static ChatService service;
    return &service;
}

ChatService::ChatService() {
    // 用户基本业务管理相关事件的回调注册
    _msgHandlerMap.insert({ LOGIN_MSG, std::bind(&ChatService::login, this, _1, _2, _3) });
    _msgHandlerMap.insert({ REG_MSG, std::bind(&ChatService::reg, this, _1, _2, _3) });
    _msgHandlerMap.insert({ ONE_CHAT_MSG, std::bind(&ChatService::oneChat, this, _1, _2, _3) });
}

void ChatService::login(const TcpConnectionPtr& conn, json& js, Timestamp time) {
    int    id  = js["id"].get<int>();
    string pwd = js["password"];

    User user = _userModel.query(id);
    if (user.getId() != -1 && user.getPassword() == pwd) {
        if (user.getState() == "online") {
            // 该用户已经登录 不允许重复登录
            json response;
            response["msgid"]  = LOGIN_MSG_ACK;
            response["errno"]  = 2;
            response["errmsg"] = "该账户已经登录!";
            conn->send(response.dump());
        } else {
            {
                // 登录成功，记录用户连接信息
                lock_guard<mutex> lock(_connMutex);
                _userConnMap.insert({ id, conn });
            }

            // 登录成功 更新用户状态信息
            user.setState("online");
            _userModel.updateState(user);

            json response;
            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = 0;
            response["id"]    = user.getId();
            response["name"]  = user.getName();
            conn->send(response.dump());
        }
    } else {
        // 该用户不存在
        json response;
        response["msgid"]  = LOGIN_MSG_ACK;
        response["errno"]  = 1;
        response["errmsg"] = "账号或密码错误!";
        conn->send(response.dump());
    }
}

void ChatService::reg(const TcpConnectionPtr& conn, json& js, Timestamp time) {
    string name = js["name"];
    string pwd  = js["password"];

    User user;
    user.setName(name);
    user.setPassword(pwd);
    bool state = _userModel.insert(user);
    if (state) {
        // 注册成功
        json response;
        response["msgid"] = REG_MSG_ACK;
        response["errno"] = 0;
        response["id"]    = user.getId();
        conn->send(response.dump());
    } else {
        // 注册失败
        json response;
        response["msgid"] = REG_MSG_ACK;
        response["errno"] = 1;
        conn->send(response.dump());
    }
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

void ChatService::clientCloseException(const TcpConnectionPtr* conn) {
}

void ChatService::oneChat(const TcpConnectionPtr& conn, json& js, Timestamp time) {
    int toid = js["to"].get<int>();

    bool userState = false; // 标识用户是否在线
    {
        lock_guard<mutex> lock(_connMutex);
        auto              it = _userConnMap.find(toid);
        if (it != _userConnMap.end()) {
            // toid在线 转发消息
            it->second->send(js.dump());
            return;
        }
    }
}
