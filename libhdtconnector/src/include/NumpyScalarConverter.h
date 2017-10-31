#ifndef NUMPY_SCALA_CONVERTER_H
// From https://stackoverflow.com/questions/26595350/extracting-unsigned-char-from-array-of-numpy-uint8
// and http://www.boost.org/doc/libs/1_62_0/libs/python/doc/html/faq/how_can_i_automatically_convert_.html
#include <iostream>
#include <boost/python.hpp>

// http://docs.scipy.org/doc/numpy/reference/c-api.array.html#importing-the-api
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
//#define PY_ARRAY_UNIQUE_SYMBOL printnum_cpp_module_PyArray_API
#include <numpy/arrayobject.h>
#include <numpy/arrayscalars.h>

template <typename ScalarType>
struct NumpyScalarConverter
{
	NumpyScalarConverter()
	{
		using namespace boost::python;
		converter::registry::push_back( &convertible, &construct, type_id<ScalarType>());
	}
	// Determine if obj_ptr is a supported numpy.number

	static void* convertible(PyObject* obj_ptr)
	{
		if (PyArray_IsScalar(obj_ptr, Float32) ||
				PyArray_IsScalar(obj_ptr, Float64) ||
				PyArray_IsScalar(obj_ptr, Int8)    ||
				PyArray_IsScalar(obj_ptr, Int16)   ||
				PyArray_IsScalar(obj_ptr, Int32)   ||
				PyArray_IsScalar(obj_ptr, Int64)   ||
				PyArray_IsScalar(obj_ptr, UInt8)   ||
				PyArray_IsScalar(obj_ptr, UInt16)  ||
				PyArray_IsScalar(obj_ptr, UInt32)  ||
				PyArray_IsScalar(obj_ptr, UInt64))
		{
			return obj_ptr;
		}
		return 0;
	}

	static void construct( PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data)
	{
		using namespace boost::python;

		// Grab pointer to memory into which to construct the C++ scalar
		void* storage = ((converter::rvalue_from_python_storage<ScalarType>*) data)->storage.bytes;

		// in-place construct the new scalar value
		ScalarType * scalar = new (storage) ScalarType;

		if (PyArray_IsScalar(obj_ptr, Float32))
			(*scalar) = PyArrayScalar_VAL(obj_ptr, Float32);
		else if (PyArray_IsScalar(obj_ptr, Float64))
			(*scalar) = PyArrayScalar_VAL(obj_ptr, Float64);
		else if (PyArray_IsScalar(obj_ptr, Int8))
			(*scalar) = PyArrayScalar_VAL(obj_ptr, Int8);
		else if (PyArray_IsScalar(obj_ptr, Int16))
			(*scalar) = PyArrayScalar_VAL(obj_ptr, Int16);
		else if (PyArray_IsScalar(obj_ptr, Int32))
			(*scalar) = PyArrayScalar_VAL(obj_ptr, Int32);
		else if (PyArray_IsScalar(obj_ptr, Int64))
			(*scalar) = PyArrayScalar_VAL(obj_ptr, Int64);
		else if (PyArray_IsScalar(obj_ptr, UInt8))
			(*scalar) = PyArrayScalar_VAL(obj_ptr, UInt8);
		else if (PyArray_IsScalar(obj_ptr, UInt16))
			(*scalar) = PyArrayScalar_VAL(obj_ptr, UInt16);
		else if (PyArray_IsScalar(obj_ptr, UInt32))
			(*scalar) = PyArrayScalar_VAL(obj_ptr, UInt32);
		else if (PyArray_IsScalar(obj_ptr, UInt64))
			(*scalar) = PyArrayScalar_VAL(obj_ptr, UInt64);

		// Stash the memory chunk pointer for later use by boost.python
		data->convertible = storage;
	}
};

#endif
