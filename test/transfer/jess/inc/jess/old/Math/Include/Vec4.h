#ifndef _MATH_VEC4_H
#define _MATH_VEC4_H

namespace Math {
	template <typename T> class Vec3;

	/// %Vec4
	template <typename T> class Vec4 {
	public:
		/// Default Constructor
				Vec4();
		/// Copy Constructor
				Vec4( const Vec4<T>& vec );
		/// Constructor
				Vec4( T _x, T _y, T _z, T _w );
		/// Destructor
				~Vec4();
		/// Axis Angle
				Vec4( const Vec3<T>& axis, const T& angle );

		/// Assignment
		Vec4<T>&	operator=( const Vec4<T>& vec );
		/// Vector Addition
		Vec4<T>&	operator+=( const Vec4<T>& vec );
		/// Scalar Addition
		Vec4<T>&	operator+=( const T& f );
		/// Scalar Multiplication
		Vec4<T>&	operator*=( const T& f );
		/// Scalar Multiplication
		Vec4<T>&	operator*=( const Vec4<T>& vec );
		/// Vector Addition
		Vec4<T>		operator+( const Vec4<T>& vec );
		/// Scalar Addition
		Vec4<T>		operator+( const T& f );
		/// Scalar Multiplication
		Vec4<T>		operator*( const T& f );
		/// Scalar Multiplication
		Vec4<T>		operator*( const Vec4<T>& vec );



		/// Dot Product
		T		dot( const Vec4<T>& vec );
		/// Normalize
		void		normalize();
		void		print();

		

		/// Data
		union {
			T	v[4];
			struct {
				T	x;
				T	y;
				T	z;
				T	w;
			};
		};
	};

	typedef Vec4<float> Vec4f;
	typedef Vec4<double> Vec4d;
}

#endif















