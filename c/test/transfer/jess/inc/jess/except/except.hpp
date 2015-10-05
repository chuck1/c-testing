#ifndef __JESS_EXCEPT_EXCEPT_HPP__
#define __JESS_EXCEPT_EXCEPT_HPP__

#include <exception>
#include <string>



namespace jess
{
	class except: public std::exception
	{
	public:
		/// error codes
		struct error_code
		{
			/// enum
			enum e
			{
				eDEFAULT = 0,
				eEXIT
			};
		};
		
		
		/**
		*   Construct a SocketException with a explanatory message.
		*   @param message explanatory message
		*	@param error code
		*   @param inclSysMsg true if system message (from strerror(errno)) should be postfixed to the user provided message
		*/
		except(const std::string& msg, int ec = error_code::eDEFAULT,bool incl_sys_msg = false ) throw();
		
		/// Provided just to guarantee that no exceptions are thrown.
		~except() throw();
		
		/**
		*   Get the exception message
		*   @return exception message
		*/
		const char* what() const throw();
		
	private:
		/// message
		std::string	message_;
		
		/// error code
		int		ec_;
	};
}	




#endif















