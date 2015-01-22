#ifndef __MESSAGE__INCLUDED__
#define __MESSAGE__INCLUDED__

#include 


namespace CharCom
{

	/// %Message
	/**

	*/
	class Message
	{
		/// Ctor
		Message();
		/// Dtor
		~Message();


	private:
		/// Type
		int		m_type;



		/// I_Com object
		I_Com*	m_com;

		/// Buffer
		char*	m_buffer;
	};


}

#endif



