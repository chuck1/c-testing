#include <ArrayDeleter.h>

template <typename T> void arraydeleter<T>::operator()(T* d) const {
	delete [] d;
}


