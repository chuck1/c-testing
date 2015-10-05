#ifndef _MATH_TRANSFORM_H
#define _MATH_TRANSFORM_H

#include "Vec3.h"
#include "Vec4.h"

namespace Math {
	/// %Transform
	template <typename T> class Transform {
	public:
		/// Default Constructor
							Transform();
		/// Assignment
		Transform<T>&		operator=( const Transform<T>& transform );

		Vec3<T>	p;
		Vec4<T>	q;
	};

	typedef Transform<float> Transformf;
	typedef Transform<double> Transformd;
}

#endif















