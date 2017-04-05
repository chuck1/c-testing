#include <Vec3.h>
#include <Vec4.h>
#include <Mat33.h>
#include <Transform.h>

template <typename T>						Math::Mat33<T>::Mat33() {
	for ( int a = 0; a < 9; a++ ) {
		v[a] = 0;
	}
}
template <typename T>						Math::Mat33<T>::Mat33( const Mat33<T>& mat ) {
	for ( int a = 0; a < 9; a++ ) {
		v[a] = mat.v[a];
	}
}
template <typename T>						Math::Mat33<T>::Mat33( Transform<T> transform ) {
	column[0].x = 1 - 2*transform.q.y*transform.q.y - 2*transform.q.z*transform.q.z;
	column[0].y = 2*transform.q.x*transform.q.y + 2*transform.q.z*transform.q.w;
	column[0].z = 2*transform.q.x*transform.q.z - 2*transform.q.y*transform.q.w;

	column[1].x = 2*transform.q.x*transform.q.y - 2*transform.q.z*transform.q.w;
	column[1].y = 1 - 2*transform.q.x*transform.q.x - 2*transform.q.z*transform.q.z;
	column[1].z = 2*transform.q.y*transform.q.z + 2*transform.q.x*transform.q.w;

	column[2].x = 2*transform.q.x*transform.q.z + 2*transform.q.y*transform.q.w;
	column[2].y = 2*transform.q.y*transform.q.z - 2*transform.q.x*transform.q.w;
	column[2].z = 1 - 2*transform.q.x*transform.q.x - 2*transform.q.y*transform.q.y;

}
template <typename T>						Math::Mat33<T>::~Mat33() {

}
template <typename T>	Math::Mat33<T>&		Math::Mat33<T>::operator=( const Mat33<T>& mat ) {
	
	return *this;
}
template <typename T>	Math::Mat33<T>&		Math::Mat33<T>::operator+=( const Mat33<T>& mat ) {
	
	return *this;
}
template <typename T>	Math::Mat33<T>&		Math::Mat33<T>::operator+=( const T& f ) {
	
	return *this;
}
template <typename T>	Math::Mat33<T>&		Math::Mat33<T>::operator*=( const T& f ) {
	
	return *this;
}
template <typename T>	Math::Mat33<T>		Math::Mat33<T>::operator+( const Mat33<T>& mat ) {
	Mat33<T> result(*this);
	result += mat;
	return result;
}
template <typename T>	Math::Mat33<T>		Math::Mat33<T>::operator+( const T& f ) {
	Mat33<T> result(*this);
	result += f;
	return result;
}
template <typename T>	Math::Mat33<T>		Math::Mat33<T>::operator*( const T& f ) {
	Mat33<T> result(*this);
	result *= f;
	return result;
}

		







template class Math::Mat33<float>;
template class Math::Mat33<double>;

























