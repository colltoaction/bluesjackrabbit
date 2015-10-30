#include <engine/Vector.h>
#include <iostream>

int main(void) {
  Vector v(0, 1);
  std::cout << v.y() << std::endl;
  return 0;
}
