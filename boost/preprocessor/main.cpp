



#include <iostream>

#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp>


#define DEFINE_ENUM(name, values)					\
	struct name {								\
		enum E {							\
			BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_VALUE, , values)	\
		};								\
		static std::string to_string(E val) {					\
			switch (val) {							\
				BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_FORMAT, , values)	\
				default:						\
											return 0;	\
			}								\
		}									\
	};

#define DEFINE_ENUM_VALUE(r, data, elem)				\
	BOOST_PP_SEQ_HEAD(elem)						\
BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(elem), 2),      \
		= BOOST_PP_SEQ_TAIL(elem), )                     \
BOOST_PP_COMMA()

#define DEFINE_ENUM_FORMAT(r, data, elem)             \
	case BOOST_PP_SEQ_HEAD(elem):                       \
		return BOOST_PP_STRINGIZE(BOOST_PP_SEQ_HEAD(elem));

struct s {
	static int i;
};



namespace foo {
DEFINE_ENUM(Type,((NONE)(0)))
}
	int main() {
		std::cout << foo::Type::to_string(foo::Type::NONE) << std::endl;
	}

