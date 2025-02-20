#include "person.h"

Person::Person()
{
}
// 使用构造器中的first_name_param来初始化成员变量first_name
Person::Person(std::string &first_name_param, std::string &last_name_param) : first_name(first_name_param), last_name(last_name_param)
{
}
std::ostream &operator<<(std::ostream &out, const Person &person)
{
  out << "Person [" << person.first_name << " " << person.last_name
      << "]";
  return out;
}
Person::~Person()
{
}