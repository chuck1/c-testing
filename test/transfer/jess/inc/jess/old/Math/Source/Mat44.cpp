#include <Vec3.h>
#include <Vec4.h>
#include <Mat44.h>
#include <Transform.h>

template <typename T>						Math::Mat44<T>::Mat44() {
	*this = Mat44<T>( Transform<T>() );
}
template <typename T>						Math::Mat44<T>::Mat44( const Mat44<T>& mat ) {
	for ( int a = 0; a < 16; a++ ) {
		v[a] = mat.v[a];
	}
}
template <typename T>						Math::Mat44<T>::Mat44( Transform<T> transform ) {
	column[0].x = 1 - 2*transform.q.y*transform.q.y - 2*transform.q.z*transform.q.z;
	column[0].y =     2*transform.q.x*transform.q.y + 2*transform.q.z*transform.q.w;
	column[0].z =     2*transform.q.x*transform.q.z - 2*transform.q.y*transform.q.w;
	column[0].w = 0;

	column[1].x =     2*transform.q.x*transform.q.y - 2*transform.q.z*transform.q.w;
	column[1].y = 1 - 2*transform.q.x*transform.q.x - 2*transform.q.z*transform.q.z;
	column[1].z =     2*transform.q.y*transform.q.z + 2*transform.q.x*transform.q.w;
	column[1].w = 0;

	column[2].x =     2*transform.q.x*transform.q.z + 2*transform.q.y*transform.q.w;
	column[2].y =     2*transform.q.y*transform.q.z - 2*transform.q.x*transform.q.w;
	column[2].z = 1 - 2*transform.q.x*transform.q.x - 2*transform.q.y*transform.q.y;
	column[2].w = 0;

	column[3].x = transform.p.x;
	column[3].y = transform.p.y;
	column[3].z = transform.p.z;
	column[3].w = 1;
}
template <typename T>						Math::Mat44<T>::~Mat44() {

}
template <typename T>	Math::Mat44<T>&		Math::Mat44<T>::operator=( const Mat44<T>& mat ) {
	
	return *this;
}
template <typename T>	Math::Mat44<T>&		Math::Mat44<T>::operator+=( const Mat44<T>& mat ) {
	
	return *this;
}
template <typename T>	Math::Mat44<T>&		Math::Mat44<T>::operator+=( const T& f ) {
	
	return *this;
}
template <typename T>	Math::Mat44<T>&		Math::Mat44<T>::operator*=( const T& f ) {
	
	return *this;
}
template <typename T>	Math::Mat44<T>&		Math::Mat44<T>::operator*=( const Mat44<T>& mat ) {
	*this = *this * mat;

	return *this;
}
template <typename T>	Math::Mat44<T>		Math::Mat44<T>::operator+( const Mat44<T>& mat ) {
	Mat44<T> result(*this);
	result += mat;
	return result;
}
template <typename T>	Math::Mat44<T>		Math::Mat44<T>::operator+( const T& f ) {
	Mat44<T> result(*this);
	result += f;
	return result;
}
template <typename T>	Math::Mat44<T>		Math::Mat44<T>::operator*( const T& f ) {
	Mat44<T> result(*this);
	result *= f;
	return result;
}

template <typename T>	Math::Mat44<T>		Math::Mat44<T>::operator*( const Mat44<T>& mat ) {
	Mat44<T> ret;
	
	for ( int a = 0; a < 4; a++ ) {
		for ( int b = 0; b < 4; b++ ) {
			ret.column[a].v[b] = 0;
			for ( int c = 0; c < 4; c++ ) {
				ret.column[a].v[b] += column[c].v[b] * mat.column[a].v[c];
			}
		}
	}

	return ret;
}







template class Math::Mat44<float>;
template class Math::Mat44<double>;







