#ifndef _MATH_VEC3_H
#define _MATH_VEC3_H

namespace Math {
	template <typename T> class Vec4;

	/// %Vec3
	template <typename T> class Vec3 {
	public:
		/// Default Constructor
				Vec3();
		/// Copy Constructor
				Vec3( const Vec3<T>& vec );
		/// Constructor
				Vec3( T _x, T _y, T _z );
		/// Destructor
				~Vec3();


		/// Assignment
		Vec3<T>&	operator=( const Vec3<T>& vec );
		/// Vector Addition
		Vec3<T>&	operator+=( const Vec3<T>& vec );
		/// Vector Subtraction
		Vec3<T>&	operator-=( const Vec3<T>& vec );
		/// Scalar Addition
		Vec3<T>&	operator+=( const T& f );
		/// Scalar Multiplication
		Vec3<T>&	operator*=( const T& f );
		/// Vector Addition
		Vec3<T>		operator+( const Vec3<T>& vec );
		/// Vector Subtraction
		Vec3<T>		operator-( const Vec3<T>& vec );
		/// Scalar Addition
		Vec3<T>		operator+( const T& f );
		/// Scalar Multiplication
		Vec3<T>		operator*( const T& f );
		
		/// Scalar Multiplication
		Vec3<T>		operator*( const Vec4<T>& q );
		Vec3<T>&	operator*=( const Vec4<T>& q );

		/// Dot Product
		T			dot( const Vec3<T>& vec );
		/// Cross Product
		Vec3<T>		cross( const Vec3<T>& vec );
		
		/// Normalize
		void		normalize();
		void		print();

		/// Data
		union {
			T	v[3];
			struct {
				T	x;
				T	y;
				T	z;
			};
		};
	};

	typedef Vec3<float> Vec3f;
	typedef Vec3<double> Vec3d;
}





#endif















