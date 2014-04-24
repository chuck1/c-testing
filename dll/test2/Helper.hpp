#ifndef HELPER_HPP
#define HELPER_HPP

#include <cstring>

template<class T> class Helper {
	public:
		Helper(char const * filename, char const * name_class) {
			handle_ = dlopen(filename, RTLD_LAZY);
			if(handle_ == NULL) {
				perror(dlerror());
				exit(0);
			}
			
			char* name_create;
			char* name_destroy;
			
			name_create = new char[strlen(name_class) + 7 + 1];
			name_destroy = new char[strlen(name_class) + 8 + 1];
			
			strcpy(name_create, name_class);
			strcpy(name_destroy, name_class);

			strcat(name_create, "_create");
			strcat(name_destroy, "_destroy");
			
			create_	= (T* (*)())dlsym(handle_, name_create);
			if(create_ == NULL) {
				perror(dlerror());
				exit(0);
			}

			destroy_ = (void (*)(T*))dlsym(handle_, name_destroy);
			if(destroy_ == NULL) {
				perror(dlerror());
				exit(0);
			}
		}
		~Helper() { dlclose(handle_); }
		
		void*		handle_;
		
		T*		(*create_)();
		void		(*destroy_)(T*);
};

#endif

