#include <iostream>
namespace pluzhnik {
void my_name() { std::cout << "pluzhnik.maksim" << std::endl; }
} // namespace pluzhnik
int main() {
  pluzhnik::my_name();
  return 0;
}
