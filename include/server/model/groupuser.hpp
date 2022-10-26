#ifndef GROUP_USER_H
#define GROUP_USER_H

#include "user.hpp"

// 群组用户 继承自User类
class GroupUser : public User {
public:
    void   setRole(const string& role) { this->role = role; }
    string getRole() const { return role; }

private:
    string role;
};

#endif // !GROUP_USER_H
