#include <Python.h>

#include "Rectangle.h"
#include "rect.h"

#include <iostream>

int main (int argc, char *argv[])
{
  int result;
  auto err = PyImport_AppendInittab("rect", PyInit_rect);
  Py_Initialize();
  auto rect_module = PyImport_ImportModule("rect");

  // initrect();
  shapes::Rectangle c_rect = shapes::Rectangle(0,0,2,1);
  result = cythonfunc(c_rect);
  std::cout<<result<<"\n";

  Py_Finalize();

  return 0;
}
