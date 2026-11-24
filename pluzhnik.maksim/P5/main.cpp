#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <ellipse.hpp>
#include <rectangle.hpp>
#include <ring.hpp>
#include <shape-utils.hpp>

namespace pluzhnik
{
  void printShapesInfo(std::ostream& out, const Shape* const* shapes, std::size_t count)
  {
    out << std::fixed << std::setprecision(2);
    for (std::size_t i = 0; i < count; ++i)
    {
      const rectangle_t frame = shapes[i]->getFrameRect();
      out << "Shape #" << (i + 1) << ": area = " << shapes[i]->getArea() << ", frame = [w: " << frame.width
          << ", h: " << frame.height << ", pos: (" << frame.pos.x << ", " << frame.pos.y << ")]\n";
    }
    const rectangle_t total_frame = getTotalFrameRect(shapes, count);
    out << "Total area = " << getTotalArea(shapes, count) << "\n"
        << "Total frame = [w: " << total_frame.width << ", h: " << total_frame.height << ", pos: (" << total_frame.pos.x
        << ", " << total_frame.pos.y << ")]\n";
  }

  void deleteShapes(Shape** shapes, std::size_t count) noexcept
  {
    for (std::size_t i = 0; i < count; ++i)
    {
      delete shapes[i];
    }
  }
}

int main()
{
  const std::size_t SHAPES_COUNT = 4;
  pluzhnik::Shape* shapes[SHAPES_COUNT] = {nullptr, nullptr, nullptr, nullptr};

  try
  {
    shapes[0] = new pluzhnik::Rectangle(4.0, 2.0, {1.0, 3.0});
    shapes[1] = new pluzhnik::Rectangle({6.0, 4.0, {-2.0, -1.0}});
    shapes[2] = new pluzhnik::Ellipse(3.0, 2.0, {0.0, 4.0});
    shapes[3] = new pluzhnik::Ring(5.0, 2.0, {-3.0, 2.0});

    std::cout << "--- Before scale ---\n";
    pluzhnik::printShapesInfo(std::cout, shapes, SHAPES_COUNT);

    double cx = 0.0;
    double cy = 0.0;
    double factor = 0.0;

    if (!(std::cin >> cx >> cy >> factor))
    {
      throw std::invalid_argument("Error: invalid scale input");
    }
    if (factor <= 0.0)
    {
      throw std::invalid_argument("Error: scale factor must be positive");
    }

    const pluzhnik::point_t scale_center{cx, cy};
    for (std::size_t i = 0; i < SHAPES_COUNT; ++i)
    {
      pluzhnik::scaleFromPoint(*shapes[i], scale_center, factor);
    }

    std::cout << "--- After scale ---\n";
    pluzhnik::printShapesInfo(std::cout, shapes, SHAPES_COUNT);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    pluzhnik::deleteShapes(shapes, SHAPES_COUNT);
    return 1;
  }

  pluzhnik::deleteShapes(shapes, SHAPES_COUNT);
  return 0;
}
