#ifndef _ARRAY_DELETER_H
#define _ARRAY_DELETER_H

template <typename T> class arraydeleter {
public:
	void operator()(T* d) const;
};



#endif















