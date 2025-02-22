#ifndef CIRCAL_H
#define CIRCAL_H

#include "shape.h"
#include <string>
#include <string_view>
#include <iostream>
#include "oval.h"

class Circle : public Oval
{
public:
  Circle() = default;
  Circle(double radius,
         std::string_view description);
  ~Circle();

  void draw() const
  {
    std::cout << "Circle::draw() called. Drawing " << m_description
              << " with radius: " << get_x_rad()
              << std::endl;
  }
};

#endif