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
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <Janus/Janus.h>
#include <Janus/JanusVariableManager.h>

using namespace janus;

namespace py = pybind11;

template <typename... Args>
using overload_cast_ = py::detail::overload_cast_impl<Args...>;

void init_JanusVariableManager(py::module_ &m)
{
  py::class_<JanusIndex>(m, "JanusIndex")
      .def(py::init<>());
  // TODO: Implement repr and str

  py::class_<JanusVariableManager, Janus>(m, "JanusVariableManager")
      .def(py::init([](std::string filename)
                    {
    JanusVariableManager jvm;
    jvm.setXmlFileName(filename);
    return jvm; }),
           py::arg("filename"))

      .def("push_back",
           overload_cast_<const JanusVariable &>()(&JanusVariableManager::push_back),
           py::arg("janus_variable"))
      .def("push_back",
           overload_cast_<const std::vector<JanusVariable> &>()(&JanusVariableManager::push_back),
           py::arg("janus_variables"))

      .def(
          "__getitem__",
          [](JanusVariableManager &jvm, const JanusIndex ji)
          { return &jvm[ji]; },
          py::arg("janus_index"),
          py::return_value_policy::reference);
}