#ifndef __JSL_DEVICE_H__
#define __JSL_DEVICE_H__

#include <SIG/signal.h>

namespace JSL
{
	/** \brief event structure
	 */
	struct event
	{
		/** \brief time
		 */
		unsigned int	time;
		/** \brief value
		 */
		short		value;
		/** \brief type
		 */
		unsigned char	type;
		/** \brief number
		 */
		unsigned char	number;
	};
	/** \brief xbox
	 */
	struct status_xbox
	{
		/** \brief button
		 */
		int		button[11];
		/** \brief x
		 */
		int		x;
		/** \brief y
		 */
		int		y;
	};
	/** \brief base
	 */
	class device
	{
public:
		device();
		void			Open(char const *);
		void			Close();
		virtual void Read();
		void Info();
	
		SIG::signal<unsigned int>* signals_;
		
		int fd_;
	};
}

#endif
