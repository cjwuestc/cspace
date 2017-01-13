#include <iostream>
typedef int (func)(int);

int add(int element) {
  std::cout << "add one time!" << std::endl;
  return (++element);
}

func* getFunction() {
  return add;
}

int main() {
  int element = 1;
  func* p = getFunction();
 
  std::cout << getFunction()(2) << std::endl;
  return 0;
}
