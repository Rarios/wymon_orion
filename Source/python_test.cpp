#include <boost/python.hpp>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#ifndef SYSTEM_WRAPPER
#include "SystemWrapper.hpp"
#endif
#ifndef WINDOW_WRAPPER
#include "WindowWrapper.hpp"
#endif

using namespace boost;

// Class, which will be exposed to Python.
/*class some_str {

public:

	void str(const std::string& val) { m_str = val; }
	std::string str() { return m_str; }

private:

	std::string m_str;

};*/

// Creating the module for Python from the C++ class.
/*BOOST_PYTHON_MODULE(my_string) {

	//using namespace boost;

	// Create appropriate function pointers, so that there is no problem with
	// name ambiguity.
	void (some_str::*set_str)(const std::string&) = &some_str::str;
	std::string (some_str::*get_str)() = &some_str::str;

	python::class_<some_str>("some_str")
		.add_property("str", get_str, set_str);

}*/

int main(int arg_c, char** arg_v) {

	// Embedding the python interpreter.
	try {
	
		// Always append a module BEFORE interpreter initialization.
		PyImport_AppendInittab("System", PyInit_System);
		PyImport_AppendInittab("Window", PyInit_Window);
		Py_Initialize();

		// Load the main namespace, so it can be passed to the exec_file
		// function.
		python::object main_module = python::import("__main__");
		python::dict main_namespace = python::extract<python::dict>(main_module.attr("__dict__"));

		python::exec_file("python_test.py", main_namespace, main_namespace);

	} catch (python::error_already_set& err) {
	
		PyErr_PrintEx(0);
		return EXIT_FAILURE;
	
	}

	Py_Finalize();

	return EXIT_SUCCESS;

}
