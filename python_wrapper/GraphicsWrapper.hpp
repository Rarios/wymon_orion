#ifndef GRAPHICS_WRAPPER
#define GRAPHICS_WRAPPER

#include <boost/python.hpp>
#include <Graphics.hpp>

//Wrapping of classes in Graphics Module

BOOST_PYTHON_MODULE(Graphics) {

	using namespace boost;
	using namespace wo;
	
	python::enum_<graphics::BlendMode::Factor>("Factor")
		.value("Zero", Zero)
		.value("One", One)
		.value("SrcColor", SrcColor)
		.value("OneMinusSrcColor", OneMinusSrcColor)
		.value("DstColor", DstColor)
		.value("OneMinusDstColor", OneMinusDstColor)
		.value("SrcAlpha", SrcAlpha)
		.value("OneMinusSrcAlpha", OneMinusSrcAlpha)
		.value("DstAlpha", DstAlpha)
		.value("OneMinusDstAlpha", OneMinusDstAlpha)
		;

	python::enum_<graphics::BlendMode::Equation>("Equation")
		.value("Add", Add)
		.value("Substract", Substract)
		;

	//Zweiter Constructor noch nicht implementiert
	python::class_<graphics::BlendMode>("BlendMode", python::init<>())
		.def(python::init<graphics::BlendMode::Factor, 
			graphics::BlendMode::Factor, graphics::BlendMode::Equation, 
			graphics::BlendMode::Factor, graphics::BlendMode::Factor,
			graphics::BlendMode::Equation>)
		.def(python::self != python::self)
		.def(python::self == python::self)
		.def_readwrite("alphaDstFactor", &graphics::BlendMode::alphaDstFactor)
		.def_readwrite("alphaEquation", &graphics::BlendMode::alphaEquation)
		.def_readwrite("alphaSrcFactor", &graphics::BlendMode::alphaSrcFactor)
		.def_readwrite("colorDstFactor", &graphics::BlendMode::colorDstFactor)
		.def_readwrite("colorEquation", &graphics::BlendMode::colorEquation)
		.def_readwrite("colorSrcFactor", &graphics::BlendMode::colorSrcFactor)
		;

	python::class_<graphics::Drawable>("Drawable");

	//Drawable::draw protected...

	//Transformable
	void move1(float offsetX, float offsetY){
		return graphics::Transformable::move(offsetX, offsetY);
	}

	void move2(const system::Vector2f& offset){
		return graphics::Transformable::move(offset);
	}

	void scale1(float factorX, float factorY){
		return graphics::Transformable::scale(factorX,factorY);
	}

	void scale2(const system::Vector2f& factor){
		return graphics::Transformable::scale(factor);
	}

	void setOrigin1(float x, float y){
		return graphics::Transformable::setOrigin(x, y);
	}

	void setOrigin2(const system::Vector2f& origin){
		return graphics::Transformable::setOrigin(origin);
	}

	void setPosition1(float x, float y){
		return graphics::Transformable::setPosition(x,y);
	}

	void setPosition2(const system::Vector2f& position){
		return graphics::Transformable::setPosition(position);
	}

	void setScale1(float factorX, float factorY){
		return graphics::Transformable::setScale(factorX, factorY);
	}

	void setScale2(const system::Vector2f& factors){
		return graphics::Transformable::setScale(factors);
	}

	python::class_<graphics::Transformable>("Transformable", python::init<>())
		.def("getInverseTransform", &graphics::Transformable::getInverseTransform,
			 python::return_internal_reference<>())
		.def("getOrigin", &graphics::Transformable::getOrigin,
			 python::return_internal_reference<>())
		.def("getPosition", &graphics::Transformable::getPosition, 
			 python::return_internal_reference<>())
		.def("getRotation", &graphics::Transformable::getRotation)
		.def("getScale", &graphics::Transformable::getScale, 
			 python::return_internal_reference<>())
		.def("getTransform", &graphics::Transformable::getTransform,
			 python::return_internal_reference<>())
		.def("move", &move1)
		.def("move", &move2)
		.def("rotate", &graphics::Transformable::rotate)
		.def("scale", &scale1)
		.def("scale", &scale2)
		.def("setOrigin", &setOrigin1)
		.def("setOrigin2", &setOrigin2)
		.def("setPosition", &setPosition1)
		.def("setPosition", &setPosition2)
		.def("setRotation", &setRotation)
		.def("setScale", &setScale1)
		.def("setScale", &setScale2)
		;

	//Transform
	graphics::Transform& rotate1(float angle, float centerX, float centerY){
		return graphics::Transform::rotate(angle, centerX,centerY);
	}

	graphics::Transform& rotate2(float angle, const system::Vector2f& center){
		return graphics::Transform::rotate(angle, center);
	}

	graphics::Transform& scale3(float scaleX, float scaleY){
		return graphics::Transform::scale(scaleX, scaleY);
	}

	graphics::Transform scale4(float scaleX, float scaleY, float centerX, 
							   float centerY){
		return graphics::Transform::scale(scaleX, scaleY, centerX, centerY);
	}

	graphics::Transform scale5(const system::Vector2f& factors){
		return graphics::Transform::scale(factors);
	}

	graphics::Transform scale6(const system::Vector2f& factors, 
							   const system::Vector2f& center){
		return graphics::Transform::scale(factors, center);
	}

	system::Vector2f transformPoint1(float x, float y){
		return graphics::Transform::transformPoint(x, y);
	}

	system::Vector2f transformPoint2(const system::Vector2f& point){
		return graphics::Transform::transformPoint(point);
	}

	graphics::Transform& translate1(float x, float y){
		return graphics::Transform::translate(x, y);
	}

	graphics::Transform& translate2(const system::Vector2f& offset){
		return graphics::Transform::translate(offset);
	}

	python::class_<graphics::Transform>("Transform", python::init<>())
		.def(python::init_<float, float, float, float, float, float, float, 
			 float, float>)
		.def("combine", &graphics::Transform::combine, 
			 python::return_internal_reference<>())
		.def("getInverse", &graphics::Transform::getInverse)
		.def("getMatrix", &graphics::Transform::getMatrix)
		.def("rotate", &rotate1, python::return_internal_reference<>())
		.def("rotate", &rotate2, python::return_internal_reference<>())
		.def("scale", &scale3, python::return_internal_reference<>())
		.def("scale", &scale4, python::return_internal_reference<>())
		.def("scale", &scale5, python::return_internal_reference<>())
		.def("scale", &scale6, python::return_internal_reference<>())
		.def("transformPoint", &transformPoint1)
		.def("transformPoint", &transformPoint2)
		.def("transformRect", &transformRect)
		.def("translate", &translate1, 
			 python::return_internal_reference<>())
		.def("translate", &translate2,
			 python::return_internal_reference<>())
		.def(const python::self& * const python::self&)
		.def(const python::self& * const system::Vector2f&)
		.def(python::self& * const python::self&, 
			 python::return_internal_reference<>())
		.def("Identity", &Identity)
		;

	

}

#endif