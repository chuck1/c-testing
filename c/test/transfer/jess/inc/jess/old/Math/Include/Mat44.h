#ifndef _MATH_MAT44_H
#define _MATH_MAT44_H

namespace Math {
	template <typename T> class Transform;
}

namespace Math {
	/// %Mat44
	template <typename T> class Mat44 {
	public:
		/// Default Constructor
					Mat44();
		/// Copy Constructor
					Mat44( const Mat44<T>& vec );
		/// Constructor
					Mat44( Transform<T> transform );
		/// Destructor
					~Mat44();
		/// Assignment
		Mat44<T>&	operator=( const Mat44<T>& );
		/// Matrix Addition
		Mat44<T>&	operator+=( const Mat44<T>& );
		/// Scalar Addition
		Mat44<T>&	operator+=( const T& );
		/// Matrix Multiplication
		Mat44<T>&	operator*=( const Mat44<T>& );
		/// Scalar Multiplication
		Mat44<T>&	operator*=( const T& );
		/// Matrix Addition
		Mat44<T>	operator+( const Mat44<T>& vec );
		/// Scalar Addition
		Mat44<T>	operator+( const T& s );
		/// Matrix Multiplication
		Mat44<T>	operator*( const Mat44<T>& );
		/// Scalar Multiplication
		Mat44<T>	operator*( const T& s );

		/// Data
		union {
			T	v[16];
			struct {
				union {
					struct {
						T	x;
						T	y;
						T	z;
						T	w;
					};
					T v[4];
				};

			} column[4];
		};
	};



	typedef Mat44<float> Mat44f;
	typedef Mat44<double> Mat44d;
}



#endif















