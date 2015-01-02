#ifndef WINDOW_WRAPPER
#define WINDOW_WRAPPER

#include <boost/python.hpp>
#include <Window.hpp>

BOOST_PYTHON_MODULE(Window) {

	using namespace boost;
	using namespace wo;



	// So ein gack, Style (enum faihlt)
	
	// Window class fehlt 2. Constructor
	// Window class fehlt 3. Constructor
	
	void create1(window::VideoMode videoMode, const system::String& str) { 
		return window::Window.create(videoMode, str);
	}

	void create2(window::VideoMode videoMode, const system::String& str, 
				 Uint32 uint) { return window::Window.create(videoMode, str, uint); }

	void create3(window::VideoMode videoMode, const system::String& str, 
				 Uint32 uint, const window::ContextSettings& settings) { 
		return window::Window.create(videoMode, str, uint, settings); 
	}

	void create4(WindowHandle handle) { return window::Window.create(handle); }

	void create5(WindowHandle handle, const ContextSettings& settings) { 
		return window::Window.create(handle, settings);
	}
	
	python::class_<window::Window>("Window", python::init<>())
		.def("close", &window::Window::close)
		.def("create", &create1)
		.def("create", &create2)
		.def("create", &create3)
		.def("create", &create4)
		.def("create", &create5)
		.def("display", &window::Window::display)
		.def("getPosition", &window::Window::getPosition)
		.def("getSettings", &window::Window::getSettings)
		.def("getSize", &window::Window::getSize)
		.def("getSystemHandle", &window::Window::getSystemHandle)
		.def("hasFocus",&window::Window::hasFocus)
		.def("isOpen", &window::Window::isOpen)
		.def(

}

#endif
