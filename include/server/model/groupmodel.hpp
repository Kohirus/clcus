#ifndef GOURP_MODEL_H
#define GOURP_MODEL_H

#include "group.hpp"
#include <string>
#include <vector>
using namespace std;

// 维护群组信息的操作类
class GroupModel {
public:
    // 创建群组
    bool createGroup(Group& group);
    // 加入群组
    void addGroup(int userid, int groupid, const string& role);
    // 查询用户所在群组信息
    vector<Group> queryGroups(int userid);
    // 根据指定的 groupid 查询群组用户 id 列表 除了userid 自己
    vector<int> queryGroupUsers(int userid, int groupid);
};

#endif // !GOURP_MODEL_H
