#include <iostream>
#include <sstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>
#include <boost/archive/polymorphic_xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

using namespace boost::archive;

#define FUNC std::cout << __PRETTY_FUNCTION__ << std::endl;

struct base
{
	virtual void			load(binary_iarchive & ar, unsigned int const & v) {}
	virtual void			save(binary_oarchive & ar, unsigned int const & v) const {}
	virtual void			load(naked_xml_iarchive & ar, unsigned int const & v) {}
	virtual void			save(naked_xml_oarchive & ar, unsigned int const & v) const {}

	virtual void			load(polymorphic_iarchive & ar, unsigned int const & v) {}
	virtual void			save(polymorphic_oarchive & ar, unsigned int const & v) const {}
	BOOST_SERIALIZATION_SPLIT_MEMBER();

};

struct foo: virtual base
{
	virtual ~foo() {}

	virtual void			load(binary_iarchive & ar, unsigned int const & v) {}
	virtual void			save(binary_oarchive & ar, unsigned int const & v) const {}
	virtual void			load(naked_xml_iarchive & ar, unsigned int const & v) {}
	virtual void			save(naked_xml_oarchive & ar, unsigned int const & v) const {}

	template<class Archive> void	__serialize(Archive & ar, unsigned int const &)
	{
		FUNC;
	}
	virtual void			load(polymorphic_iarchive & ar, unsigned int const & v)
	{
		FUNC;
		__serialize(ar, v);
	}
	virtual void			save(polymorphic_oarchive & ar, unsigned int const & v) const
	{
		FUNC;
		const_cast<foo*>(this)->__serialize(ar, v);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();
};

//BOOST_CLASS_EXPORT_GUID(foo,"foo");

struct bar: virtual foo
{
	virtual void			load(binary_iarchive & ar, unsigned int const & v) {}
	virtual void			save(binary_oarchive & ar, unsigned int const & v) const {}
	virtual void			load(naked_xml_iarchive & ar, unsigned int const & v) {}
	virtual void			save(naked_xml_oarchive & ar, unsigned int const & v) const {}

	template<class Archive> void	__serialize(Archive & ar, unsigned int const &)
	{
		FUNC;
		b = 10;
		ar & BOOST_SERIALIZATION_NVP(b);
	}
	virtual void			load(polymorphic_iarchive & ar, unsigned int const & v)
	{
		FUNC;
		
		BOOST_SERIALIZATION_BASE_OBJECT_NVP(foo);
		
		//ar & boost::serialization::make_nvp(
		//		"foo",
		//		boost::serialization::base_object<foo>(*this));
		
		foo::__serialize(ar,v);
		
		__serialize(ar, v);
	}
	virtual void			save(polymorphic_oarchive & ar, unsigned int const & v) const
	{
		FUNC;
		
		BOOST_SERIALIZATION_BASE_OBJECT_NVP(foo);
		
		//ar & boost::serialization::make_nvp(
		//		"foo",
		//		boost::serialization::base_object<foo>(*this));
		
		const_cast<bar*>(this)->foo::__serialize(ar,v);
		
		const_cast<bar*>(this)->__serialize(ar, v);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER();
	
	float b;
};

int main()
{
	FUNC;
	
	
	std::stringstream ss;

	{
		polymorphic_xml_oarchive ar(ss);

		ar.template register_type<base>();
		ar.template register_type<foo>();
		ar.template register_type<bar>();

		bar* f = new bar;

		ar & f;
	}

	std::cout << ss.str() << std::endl;

	polymorphic_xml_iarchive ar2(ss);
	ar2.template register_type<base>();
	ar2.template register_type<foo>();
	ar2.template register_type<bar>();

	foo* f2 = 0;

	ar2 & f2;

}




