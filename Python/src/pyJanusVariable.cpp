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
#include <Janus/Janus.h>
#include <Janus/JanusVariable.h>
#include <Ute/aString.h>

using namespace janus;
using namespace dstoute;

namespace py = pybind11;

template <typename... Args>
using overload_cast_ = py::detail::overload_cast_impl<Args...>;

void init_JanusVariable(py::module_ &m)
{
  m.attr("janusMandatory") = janusMandatory;
  m.attr("janusRequired") = janusRequired;

  py::class_<JanusVariable>(m, "JanusVariable")
      .def(py::init<const std::string &, JanusVariableType, bool, const double &>(),
           py::arg("variable_name"),
           py::arg("variable_type"),
           py::arg("is_mandatory"),
           py::arg("value"))
      .def(py::init<const std::string &, JanusVariableType, bool, const std::string &, const double &>(),
           py::arg("variable_name"),
           py::arg("variable_type"),
           py::arg("is_mandatory"),
           py::arg("specific_units"),
           py::arg("value"))

      .def("is_initialised", &JanusVariable::isInitialised)
      .def("is_available", &JanusVariable::isAvailable)
      .def("is_missing", &JanusVariable::isMissing)
      .def("is_mandatory", &JanusVariable::isMandatory)

      .def("as_str", &JanusVariable::stringValue)

      .def_property_readonly("initial_value", &JanusVariable::getInitialValue)
      .def_property_readonly("name", &JanusVariable::getName)
      .def_property_readonly("units", &JanusVariable::getUnits)
      .def_property_readonly("var_id", &JanusVariable::getVarID)

      .def("get_value", &JanusVariable::value)
      .def("set_value", &JanusVariable::setValue, py::arg("value"))

      .def("__repr__",
           [](JanusVariable &self)
           {
             std::ostringstream out;
             out << "JanusVariable("
                 << "name='" << self.getName() << "', "
                 << "var_id='" << self.getVarID() << "', "
                 << "units='" << self.getUnits() << "', "
                 << "initial_value='" << self.getInitialValue() << "', "
                 << "value='" << self.value() << "')";
             return out.str();
           })
      .def("__str__",
           [](const JanusVariable &self)
           {
             std::ostringstream out;
             out << self.getName() << ": " << self.value() << " " << self.getUnits();
             return out.str();
           });

  py::enum_<JanusVariableType>(m, "JanusVariableType")
      .value("janusOutputVariable", JanusVariableType::janusOutputVariable)
      .value("janusInputVariable", JanusVariableType::janusInputVariable)
      .value("janusInputOutputVariable", JanusVariableType::janusInputOutputVariable)
      .value("janusDeltaOutputVariable", JanusVariableType::janusDeltaOutputVariable)
      .value("janusDeltaInputVariable", JanusVariableType::janusDeltaInputVariable)
      .value("janusDeltaInputOutputVariable", JanusVariableType::janusDeltaInputOutputVariable)
      .value("janusIgnoreUnitsOutputVariable", JanusVariableType::janusIgnoreUnitsOutputVariable)
      .value("janusIgnoreUnitsInputVariable", JanusVariableType::janusIgnoreUnitsInputVariable)
      .value("janusIgnoreUnitsInputOutputVariable", JanusVariableType::janusIgnoreUnitsInputOutputVariable)
      .value("janusString", JanusVariableType::janusString)
      .export_values();
}