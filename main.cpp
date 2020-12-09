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

  // do same through Python
  PyObject *py_rect = PyObject_GetAttrString(rect_module, "PyRectangle");
  
  PyObject *pargs = PyTuple_New(4);
  {
      PyObject * pv;
      pv = PyLong_FromLong(0);
      PyTuple_SetItem(pargs, 0, pv);
      pv = PyLong_FromLong(0);
      PyTuple_SetItem(pargs, 1, pv);
      pv = PyLong_FromLong(2);
      PyTuple_SetItem(pargs, 2, pv);
      pv = PyLong_FromLong(1);
      PyTuple_SetItem(pargs, 3, pv);

      pv = PyObject_CallObject(py_rect, pargs);
      if (pv != nullptr && (PyObject_TypeCheck(pv, &c_PyRect_t))) {
	  PyObject *get_area_method;
	  get_area_method = PyObject_GetAttrString(pv, "get_area");
	  if (get_area_method != nullptr) {
	      PyObject *res_v = PyObject_CallObject(get_area_method, PyTuple_New(0));
	      printf("Result of call to get_area is : %ld\n", PyLong_AsLong(res_v));
	      Py_DECREF(res_v);
	  }

	  struct c_PyRect * c_pv = reinterpret_cast<struct c_PyRect *>(pv);
	  int res = cythonfunc2(c_pv);
	  std::cout << "Result of cythonfunc2 is " << res << std::endl;
      } else {
	  Py_DECREF(pargs);
	  Py_DECREF(py_rect);
	  Py_DECREF(rect_module);
	  PyErr_Print();
	  std::cerr <<  "Call failed!" << std::endl;
	  return 1;
      }
  }

  Py_DECREF(pargs);

  Py_XDECREF(py_rect);
  Py_XDECREF(rect_module);
  Py_Finalize();

  return 0;
}
