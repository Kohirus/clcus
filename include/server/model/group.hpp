#ifndef GROUP_H
#define GROUP_H

#include "groupuser.hpp"
#include <string>
#include <vector>

using namespace std;

// User表示的 ORM 类
class Group {
public:
    Group(int id = -1, const string& name = "", const string& desc = "")
        : _id(id)
        , _name(name)
        , _desc(desc) { }

    void setId(int id) { _id = id; }
    void setName(const string& name) { _name = name; }
    void setDesc(const string& desc) { _desc = desc; }

    int    getId() const { return _id; }
    string getName() const { return _name; }
    string getDesc() const { return _desc; }

    vector<GroupUser>& getUsers() { return users; }

private:
    int    _id;
    string _name;
    string _desc;

    vector<GroupUser> users;
};

#endif // !GROUP_H
