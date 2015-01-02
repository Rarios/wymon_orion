#ifndef SYSTEM_WRAPPER
#define SYSTEM_WRAPPER

#include <boost/python.hpp>
#include <System.hpp>

BOOST_PYTHON_MODULE(System) {

	using namespace boost;
	using namespace wo;

	python::class_<system::NonCopyable>("NonCopyable", python::no_init);
	
	
	python::class_<system::Time>("Time", python::init<>())
		.def("asSeconds", &system::Time::asSeconds)
		.def("asMilliseconds", &system::Time::asMilliseconds)
		.def("asMicroseconds", &system::Time::asMicroseconds)
		.def(python::self == python::self)
		.def(python::self != python::self)
		.def(python::self < python::self)
		.def(python::self > python::self)
		.def(python::self <= python::self)
		.def(python::self >= python::self)
		.def(- python::self)
		.def(+ python::self)
		.def(python::self += python::self, python::return_internal_reference<>())
		.def(python::self - python::self)
		.def(python::self -= python::self, python::return_internal_reference<>())
		.def(python::self * float())
		.def(python::self * Int64())
		.def(float() * python::self)
		.def(Int64() * python::self)
		.def(python::self *= float(), python::return_internal_reference<>())
		.def(python::self *= Int64(), python::return_internal_reference<>())
		.def(python::self / float())
		.def(python::self / Int64())
		.def(python::self /= float(), python::return_internal_reference<>())
		.def(python::self /= Int64(), python::return_internal_reference<>())
		.def(python::self / python::self)
		.def(python::self % python::self)
		.def(python::self %= python::self, python::return_internal_reference<>())
		;
		
	python::def("seconds", &system::seconds);
	python::def("milliseconds", &system::milliseconds);
	python::def("microseconds", &system::microseconds);
		
		
	python::class_<system::Clock>("Clock", python::init<>())
		.def("getElapsedTime", &system::Clock::getElapsedTime)
		.def("restart", &system::Clock::restart)
		;
		
		struct InputStreamWrap : system::InputStream, wrapper<system::InputStream> {
    			
    		read (void *data, Int64 size) {
    		
    			return this->get_override("read")();
    		
    		}
        	
        	seek (Int64 position) {
    		
    			return this->get_override("seek")();
    		
    		}
    		
    		tell () {
    		
    			return this->get_override("tell")();
    		
    		}
    		
    		getSize (){
    		
    			return this->get_override("getSize")();
    		
    		}
    	}

	python::class_<system::InputStream , noncopyable>("InputStream", python::no_init)
		 .def("read", pure_virtual(&InputStream::read))
		 .def("seek", pure_virtual(&InputStream::seek))
		 .def("tell", pure_virtual(&InputStream::tell))
		 .def("getSize", pure_virtual(&InputStream::getSize))
		 ;
		 
	python::class_<system::String>("String", python::init<>())
		.def(init<const char*>()) //WARNING: Second parameter are missing!
		.def(init<const std::string&>()) //WARNING: Second parameter are missing!
		;
		
	python::class_<system::Vector2<int>>("Vector2i")
		.def(init<int, int>())
		.def_readwrite("x", &Vector2<int>::x)
		.def_readwrite("y", &Vector2<int>::y)
		;
	
	python::class_<system::Vector2<float>>("Vector2f")
		.def(init<float, float>())
		.def_readwrite("x", &Vector2<float>::x)
		.def_readwrite("y", &Vector2<float>::y)
		;
	//Operators of Vector2 are missing!!
		
}

#endif
