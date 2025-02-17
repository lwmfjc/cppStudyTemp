#include <iostream>

int main()
{

  /* int *p_number{};
  double *p_fractional_number{};
  std::cout << sizeof(p_number) << std::endl;
  std::cout << sizeof(p_fractional_number) << std::endl;

  //p_number指针,my_num是int
  int * p_number7{},my_num{}; */

  int int_var{43};
  int *p_int{&int_var};

  std::cout << int_var << std::endl;
  std::cout << p_int << std::endl;
  std::cout << "size[" << sizeof(p_int) << "]" << std::endl;
  std::cout << *p_int << std::endl;
  return 0;
}