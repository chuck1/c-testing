#include <cmath>
#include <stdio.h>

#include <Vec4.h>
#include <Vec3.h>



template <typename T>					Math::Vec3<T>::Vec3(): x(0), y(0), z(0) {

}
template <typename T>					Math::Vec3<T>::Vec3( const Vec3<T>& vec ): x(vec.x), y(vec.y), z(vec.z) {
	
}
template <typename T>					Math::Vec3<T>::Vec3( T _x, T _y, T _z ): x(_x), y(_y), z(_z) {

}
template <typename T>					Math::Vec3<T>::~Vec3() {

}
template <typename T>	Math::Vec3<T>&	Math::Vec3<T>::operator=( const Vec3<T>& vec ) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
}

template <typename T>	Math::Vec3<T>&	Math::Vec3<T>::operator+=( const Vec3<T>& vec ) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}
template <typename T>	Math::Vec3<T>&	Math::Vec3<T>::operator-=( const Vec3<T>& vec ) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}
template <typename T>	Math::Vec3<T>&	Math::Vec3<T>::operator+=( const T& f ) {
	x += f;
	y += f;
	z += f;
	return *this;
}
template <typename T>	Math::Vec3<T>&	Math::Vec3<T>::operator*=( const T& f ) {
	x *= f;
	y *= f;
	z *= f;
	return *this;
}
template <typename T>	Math::Vec3<T>	Math::Vec3<T>::operator+( const Vec3<T>& vec ) {
	Vec3<T> result(*this);
	result += vec;
	return result;
}
template <typename T>	Math::Vec3<T>	Math::Vec3<T>::operator-( const Vec3<T>& vec ) {
	Vec3<T> result(*this);
	result -= vec;
	return result;
}
template <typename T>	Math::Vec3<T>	Math::Vec3<T>::operator+( const T& f ) {
	Vec3<T> result(*this);
	result += f;
	return result;
}
template <typename T>	Math::Vec3<T>	Math::Vec3<T>::operator*( const T& f ) {
	Vec3<T> result(*this);
	result *= f;
	return result;
}
template <typename T>	Math::Vec3<T>	Math::Vec3<T>::operator*( const Vec4<T>& q ) {
	Vec4<T> c( -q.x, -q.y, -q.z, q.w );

	Vec4<T> v( x, y, z, 0 );

	Vec4<T> r = (c*v)*q;

	Vec3<T> res(r.x,r.y,r.z);

	return res;
}
template <typename T>	Math::Vec3<T>&	Math::Vec3<T>::operator*=( const Vec4<T>& q ) {
	*this = *this * q;

	return *this;
}



template <typename T>	T				Math::Vec3<T>::dot( const Vec3<T>& vec ) {
	return ( ( x * vec.x ) + ( y * vec.y ) + ( z * vec.z ) );
}
template <typename T>	Math::Vec3<T>	Math::Vec3<T>::cross( const Vec3<T>& vec ) {
	return Vec3<T>( y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x );
}
template <typename T>	void			Math::Vec3<T>::normalize() {
	T len = sqrt( x*x + y*y + z*z );
	*this *= (1/len);
}
template <typename T>	void			Math::Vec3<T>::print() {
	printf("%f %f %f\n",x,y,z);
}









template class Math::Vec3<float>;
template class Math::Vec3<double>;









