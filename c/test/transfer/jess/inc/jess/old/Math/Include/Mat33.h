#ifndef _MATH_MAT33_H
#define _MATH_MAT33_H

namespace Math {
	template <typename T> class Transform;
}

namespace Math {
	/// %Mat33
	template <typename T> class Mat33 {
	public:
		/// Default Constructor
					Mat33();
		/// Copy Constructor
					Mat33( const Mat33<T>& vec );
		/// Constructor
					Mat33( Transform<T> transform );
		/// Destructor
					~Mat33();
		
					

		/// Assignment
		Mat33<T>&	operator=( const Mat33<T>& vec );
		/// Vector Addition
		Mat33<T>&	operator+=( const Mat33<T>& vec );
		/// Scalar Addition
		Mat33<T>&	operator+=( const T& s );
		/// Scalar Multiplication
		Mat33<T>&	operator*=( const T& s );
		


		/// Vector Addition
		Mat33<T>	operator+( const Mat33<T>& vec );
		/// Scalar Addition
		Mat33<T>	operator+( const T& s );
		/// Scalar Multiplication
		Mat33<T>	operator*( const T& s );



		/// Data
		union {
			T	v[9];
			struct {
				T	x;
				T	y;
				T	z;
			} column[3];
		};
	};



	typedef Mat33<float> Mat33f;
	typedef Mat33<double> Mat33d;
}



#endif















