#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>

class Person
{
  // 重载<<运算符,且<<为友元函数，使之可以访问private成员
  friend std::ostream &operator<<(std::ostream &out, const Person &person);

public:
  Person();
  Person(std::string &first_name_param, std::string &last_name_param);
  ~Person();
  // 限制类的成员函数不能对成员变量进行修改
  std::string get_first_name() const
  {
    return first_name;
  }
  std::string get_last_name() const
  {
    return last_name;
  }

private:
  int a = 3;
  std::string first_name{"Mysterious"};
  std::string last_name{"Person"};
};

#endif