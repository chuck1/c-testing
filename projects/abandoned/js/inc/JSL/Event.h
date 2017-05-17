#ifndef __NEBULA_PLATFORM_JOYSTICK_HPP__
#define __NEBULA_PLATFORM_JOYSTICK_HPP__

#include <map>

#include <SIG/signal.h>

#include <JSL/device.h>
#include <JSL/axes_abs.h>

namespace JSL
{
	class Event:
		public JSL::device
	{			
		public:
			enum flag: __u32
			{
				PRINT = 1 << 0
			};

			Event();
			void	Init();
			void Set(unsigned int);
			void Read();
			void Launch();
			void Join();

			void	query(__u32, __u32, std::map<__u32,char const *> );
			void	query_abs();
			void	query_absinfo(__u32);


			pthread_t thread_;

			std::map<unsigned int,char const *> map_ev;
			std::map<unsigned int,char const *> map_rel;
			std::map<unsigned int,char const *> map_abs_str_;
			std::map<unsigned int,char const *> map_key;
			std::map<unsigned int,char const *> map_msc;
			std::map<unsigned int,char const *> map_ff;


			std::map<__s32,JSL::axes_abs> map_abs_;


			SIG::signal<__u16,__s32>		sig_key_;
			std::map<__u16,SIG::signal<__s32> >	map_sig_key_;

			SIG::signal<__u16,float>		sig_abs_;
			std::map<__u16,SIG::signal<float> >	map_sig_abs_;

			SIG::signal<__u16,__s32>		sig_rel_;
			std::map<__u16,SIG::signal<__s32> >	map_sig_rel_;


			unsigned int flag_;
	};
}

#endif
