#pragma once
#include <typeinfo>

namespace Common
{
	template<class T1,class T2>
	T1* RecastClass(T1* t) {
		if (typeid(t) == typeid(T2))
		{
			return static_cast<T2*>(t);
		}
		return nullptr;
	}
}
