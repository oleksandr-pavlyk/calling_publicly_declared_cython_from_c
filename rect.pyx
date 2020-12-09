# distutils: language = c++
# distutils: sources = Rectangle.cpp

cimport numpy as cnp
cnp.import_array()

cdef extern from "Rectangle.h" namespace "shapes":
    cdef cppclass Rectangle:
        Rectangle() except +
        Rectangle(int, int, int, int) except +
        int x0, y0, x1, y1
        int getArea()

cdef public class PyRectangle [object c_PyRect, type c_PyRect_t]:
    cdef Rectangle c_rect
    def __cinit__(self, int x0, int y0, int x1, int y1):
        self.c_rect = Rectangle(x0, y0, x1, y1)
    def get_area(self):
        return self.c_rect.getArea()


cdef public int cythonfunc(Rectangle c_rect):
    result = c_rect.getArea()
    return result

cdef public int cythonfunc2(PyRectangle py_rect):
    return py_rect.get_area()
