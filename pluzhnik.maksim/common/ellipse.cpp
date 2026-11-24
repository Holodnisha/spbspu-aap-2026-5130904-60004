#include "ellipse.hpp"

#include <stdexcept>

namespace

{

constexpr double PI = 3.14159265358979323846;

}

pluzhnik::Ellipse::Ellipse(double rx, double ry, const point_t &pos)
    :

      rx_(rx),

      ry_(ry),

      pos_(pos)

{
  if (rx_ <= 0.0 || ry_ <= 0.0)

  {
    throw std::invalid_argument("Ellipse radii must be positive");
  }
}

double pluzhnik::Ellipse::getArea() const

{
  return PI * rx_ * ry_;
}

pluzhnik::rectangle_t pluzhnik::Ellipse::getFrameRect() const

{
  return {2.0 * rx_, 2.0 * ry_, pos_};
}

void pluzhnik::Ellipse::move(const point_t &pos)

{
  pos_ = pos;
}

void pluzhnik::Ellipse::move(double dx, double dy)

{
  pos_.x += dx;

  pos_.y += dy;
}

void pluzhnik::Ellipse::scale(double factor)

{
  if (factor <= 0.0)

  {
    throw std::invalid_argument("Scale factor must be positive");
  }

  rx_ *= factor;

  ry_ *= factor;
}

pluzhnik::Shape *pluzhnik::Ellipse::clone() const

{
  return new Ellipse(*this);

  et
