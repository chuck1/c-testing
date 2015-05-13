#include <cmath>
#include <stdio.h>

#include <Vec3.h>
#include <Vec4.h>



template <typename T>					Math::Vec4<T>::Vec4(): x(0), y(0), z(0), w(0) {

}
template <typename T>					Math::Vec4<T>::Vec4( const Vec4<T>& vec ): x(vec.x), y(vec.y), z(vec.z), w(vec.w) {
	
}
template <typename T>					Math::Vec4<T>::Vec4( T _x, T _y, T _z, T _w ): x(_x), y(_y), z(_z), w(_w) {

}
template <typename T>					Math::Vec4<T>::~Vec4() {

}
template <typename T>					Math::Vec4<T>::Vec4( const Vec3<T>& axis, const T& angle ) {
	w = cos( angle/2.0 );
	x = axis.x * sin( angle/2.0 );
	y = axis.y * sin( angle/2.0 );
	z = axis.z * sin( angle/2.0 );
}

template <typename T>	Math::Vec4<T>&	Math::Vec4<T>::operator=( const Vec4<T>& vec ) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
	return *this;
}



template <typename T>	Math::Vec4<T>&	Math::Vec4<T>::operator+=( const Vec4<T>& vec ) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
	return *this;
}
template <typename T>	Math::Vec4<T>&	Math::Vec4<T>::operator+=( const T& f ) {
	x += f;
	y += f;
	z += f;
	w += f;
	return *this;
}
template <typename T>	Math::Vec4<T>&	Math::Vec4<T>::operator*=( const T& f ) {
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}
template <typename T>	Math::Vec4<T>	Math::Vec4<T>::operator+( const Vec4<T>& vec ) {
	Vec4<T> result(*this);
	result += vec;
	return result;
}
template <typename T>	Math::Vec4<T>	Math::Vec4<T>::operator+( const T& f ) {
	Vec4<T> result(*this);
	result += f;
	return result;
}
template <typename T>	Math::Vec4<T>	Math::Vec4<T>::operator*( const T& f ) {
	Vec4<T> result(*this);
	result *= f;
	return result;
}
template <typename T>	Math::Vec4<T>	Math::Vec4<T>::operator*( const Vec4<T>& vec ) {
	Vec4<T> result;
	result.w = w * vec.w   -   x * vec.x   -   y * vec.y   -   z * vec.z;
	result.x = w * vec.x   +   x * vec.w   -   y * vec.z   +   z * vec.y;
	result.y = w * vec.y   +   x * vec.z   +   y * vec.w   -   z * vec.x;
	result.z = w * vec.z   -   x * vec.y   +   y * vec.x   +   z * vec.w;

	return result;
}
template <typename T>	Math::Vec4<T>&	Math::Vec4<T>::operator*=( const Vec4<T>& vec ) {
	*this = *this * vec;

	return *this;
}



template <typename T>	T				Math::Vec4<T>::dot( const Vec4<T>& vec ) {
	return ( ( x * vec.x ) + ( y * vec.y ) + ( z * vec.z ) + ( w * vec.w ) );
}
template <typename T>	void			Math::Vec4<T>::normalize() {
	T len = sqrt( x*x + y*y + z*z + w*w );
	*this *= (1/len);
}
template <typename T>	void			Math::Vec4<T>::print() {
	printf("%f %f %f %f\n",x,y,z,w);
}








template class Math::Vec4<float>;
template class Math::Vec4<double>;












