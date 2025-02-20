#include <iostream>
#include "player.h"

class B
{
private:
  int age;
};
class A : public B
{
private:
  int c;
};
int main()
{
  A a;
  Player p1("Basketball");
  std::cout << "player:" << p1 << std::endl;

  return 0;
}