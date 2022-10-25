#include "db.hpp"
#include <muduo/base/Logging.h>
#include <mysql/mysql.h>

using namespace muduo;

MySQL::MySQL() {
    _conn = mysql_init(nullptr);
}

// 释放数据库连接资源
MySQL::~MySQL() {
    if (_conn != nullptr) {
        mysql_close(_conn);
    }
}

// 连接数据库
bool MySQL::connect() {
    MYSQL* p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
        password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr) {
        // C/C++ 代码默认的编码字符是 ASCII 如果不设置 从 MySQL 读取来的中文数据无法显示
        mysql_query(_conn, "set names gdk");
        LOG_INFO << "Connected database successfully!";
    } else {
        LOG_INFO << "Failed to connect database!";
    }
    return p;
}

// 更新数据库
bool MySQL::update(string sql) {
    if (mysql_query(_conn, sql.c_str())) {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "Failed to update!";
        return false;
    }
    return true;
}

// 查询数据库
MYSQL_RES* MySQL::query(string sql) {
    if (mysql_query(_conn, sql.c_str())) {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "Failed to search!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}
