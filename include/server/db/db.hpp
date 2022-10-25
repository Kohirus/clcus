#ifndef DB_H
#define DB_H

#include <string>

using namespace std;
class MYSQL;
class MYSQL_RES;

// 数据库配置信息
static string server   = "127.0.0.1";
static string user     = "root";
static string password = "likehan";
static string dbname   = "chat";

// 数据库操作类
class MySQL {
public:
    // 初始化数据库连接
    MySQL();
    // 释放数据库连接资源
    ~MySQL();
    // 连接数据库
    bool connect();
    // 更新数据库
    bool update(string sql);
    // 查询数据库
    MYSQL_RES* query(string sql);
    // 获取连接
    MYSQL* getConnection() const { return _conn; }

private:
    MYSQL* _conn;
};

#endif // !DB_H
