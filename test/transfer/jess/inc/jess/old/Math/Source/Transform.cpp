#include <Transform.h>


template <typename T>						Math::Transform<T>::Transform() {
	p = Vec3<T>(0,0,0);
	q = Vec4<T>(0,0,0,1);
}
template <typename T>	Math::Transform<T>&	Math::Transform<T>::operator=( const Transform<T>& transform ) {
	p = transform.p;
	q = transform.q;

	return *this;
}




template class Math::Transform<float>;
template class Math::Transform<double>;



//template Math::Transform<float>&	Math::Transform<float>::operator=(const Math::Transform<float>&);
//template Math::Transform<double>&	Math::Transform<double>::operator=(const Math::Transform<double>&);


void test( const Math::Transformf &a ) {
	Math::Transformf b = a;
	b = a;
}




