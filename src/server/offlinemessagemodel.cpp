#include "offlinemessagemodel.hpp"
#include "db.hpp"
#include <mysql/mysql.h>

bool OfflineMsgModel::insert(int userid, string msg) {
    // 组装sql语句
    char sql[1024] = { 0 };
    sprintf(sql, "INSERT INTO OfflineMessage VALUES(%d, '%s')", userid, msg.c_str());

    MySQL mysql;
    if (mysql.connect()) {
        if (mysql.update(sql)) {
            return true;
        }
    }
    return false;
}

bool OfflineMsgModel::remove(int userid) {
    // 组装sql语句
    char sql[1024] = { 0 };
    sprintf(sql, "DELETE FROM OfflineMessage WHERE userid = %d", userid);

    MySQL mysql;
    if (mysql.connect()) {
        if (mysql.update(sql)) {
            return true;
        }
    }
    return false;
}

vector<string> OfflineMsgModel::query(int userid) {
    char sql[1024] = { 0 };
    sprintf(sql, "SELECT message FROM OfflineMessage WHERE userid = %d", userid);

    MySQL          mysql;
    vector<string> vec;
    if (mysql.connect()) {
        MYSQL_RES* res = mysql.query(sql);
        if (res != nullptr) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr) {
                vec.push_back(row[0]);
            }
            mysql_free_result(res);
        }
    }
    return vec;
}
