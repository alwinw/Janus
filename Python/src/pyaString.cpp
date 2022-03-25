//
// pyJanus (Python Bindings for Janus)
//
// Copyright (c) 2022 Alwin Wang
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <pybind11/pybind11.h>
#include <Ute/aString.h>

using namespace dstoute;

namespace py = pybind11;

void init_aString(py::module_ &m)
{
  py::class_<aString>(m, "aString")
      .def(py::init<const std::string &>(), py::arg("str"))

      .def("__repr__",
           [](const aString &self)
           {
             std::ostringstream out;
             out << "aString('" << self << "')";
             return out.str();
           })
      .def("__str__",
           [](const aString &self)
           {
             std::ostringstream out;
             out << self;
             return out.str();
           });

  py::class_<aFileString, aString>(m, "aFileString")
      .def(py::init<const std::string &>(), py::arg("str"))

      .def("__repr__",
           [](const aFileString &self)
           {
             std::ostringstream out;
             out << "aString('" << self << "')";
             return out.str();
           })
      .def("__str__",
           [](const aFileString &self)
           {
             std::ostringstream out;
             out << self;
             return out.str();
           });

  py::implicitly_convertible<std::string, aString>();
  py::implicitly_convertible<std::string, aFileString>();
}