#ifndef _COMM_H
#define _COMM_H

#include <queue>

namespace CharCom
{

	class Message;


	/// Interface Com
	class I_Com
	{
	public:
		

		/// Ctor
									I_Com();
		/// Dtor
		virtual						~IComm();
		


		/// post message to this object
				void 				Post(Message*);
		/// Process all messages
				void 				ProcessAll();
		/// Process message
		virtual	void 				Process(Message*) = 0;


	private:
		/// message FIFO queue
		std::queue<Message*>		m_messages;


	};




}

#endif




