#include <ring.hpp>

#include <stdexcept>

namespace

{

  constexpr double PI = 3.14159265358979323846;

}

pluzhnik::Ring::Ring(double outer_r, double inner_r, const point_t& pos):

  outer_r_(outer_r),

  inner_r_(inner_r),

  pos_(pos)

{
  if (outer_r_ <= 0.0 || inner_r_ <= 0.0)

  {
    throw std::invalid_argument("Ring radii must be positive");
  }

  if (inner_r_ >= outer_r_)

  {
    throw std::invalid_argument("Inner radius must be strictly less than outer radius");
  }
}

double pluzhnik::Ring::getArea() const

{
  return PI * (outer_r_ * outer_r_ - inner_r_ * inner_r_);
}

pluzhnik::rectangle_t pluzhnik::Ring::getFrameRect() const

{
  const double diameter = 2.0 * outer_r_;

  return {diameter, diameter, pos_};
}

void pluzhnik::Ring::move(const point_t& pos)

{
  pos_ = pos;
}

void pluzhnik::Ring::move(double dx, double dy)

{
  pos_.x += dx;

  pos_.y += dy;
}

void pluzhnik::Ring::scale(double factor)

{
  if (factor <= 0.0)

  {
    throw std::invalid_argument("Scale factor must be positive");
  }

  outer_r_ *= factor;

  inner_r_ *= factor;
}

pluzhnik::Shape* pluzhnik::Ring::clone() const

{
  return new Ring(*this);
}
