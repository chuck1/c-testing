#ifndef __UTILITIES_PTR_INCLUDED__
#define __UTILITIES_PTR_INCLUDED__


/// %Ptr
/**
* Holds a pointer and provides general functionality for public access.
*/
template <class T> class Ptr {
public:
	/// Ctor
			Ptr();
	/// Dtor
			~Ptr();
			
	/// Get
	T*		Get() const;
	/// Get or error
	T*		Get_Or_Error() const;
	/// Set
	void	Set(T* const);
	/// Set or error
	void	Set_Or_Error(T* const);
protected:
	/// Pointer
	T*	m_ptr;
};




#endif




