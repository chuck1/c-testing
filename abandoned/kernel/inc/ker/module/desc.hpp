#ifndef __KERNEL_MODULE_DESC_HPP__
#define __KERNEL_MODULE_DESC_HPP__

#include <memory>

#include <ker/ns.hpp>
#include <ker/module/type.hpp>
#include <ker/module/mode.hpp>

namespace ker
{
	namespace module
	{
		/** \brief module description
		*/
		struct desc
		{
			/** \brief type
			*/
			ker::module::type				type_;
			/** \brief mode
			 * CREATE, FIND,
			 */
			ker::module::mode				mode_;
			/** \brief parent
			 * if null, call request( desc_parent_ )
			 */
			std::weak_ptr<ker::module::module>		parent_;
			/** \brief parent descripion
			*/
			std::shared_ptr<ker::module::desc>		desc_parent_;
		};
	}
}

#endif
