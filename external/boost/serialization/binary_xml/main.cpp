
#include <iostream>
#include <sstream>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>
#include <boost/archive/polymorphic_xml_oarchive.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

using namespace boost::archive;

typedef polymorphic_iarchive PI;
typedef polymorphic_oarchive PO;
typedef polymorphic_binary_iarchive BI;
typedef polymorphic_binary_oarchive BO;
typedef polymorphic_xml_iarchive XI;
typedef polymorphic_xml_oarchive XO;
/*
typedef binary_iarchive BI;
typedef binary_oarchive BO;
typedef xml_iarchive XI;
typedef xml_oarchive XO;
*/
struct foo
{
	void save(PO & ar, unsigned int const & version) const {
		//BO* b = dynamic_cast<BO*>(&ar);
		//XO* x = dynamic_cast<XO*>(&ar);
		//std::cout << b << " " << x << std::endl;
	}
	void load(PI & ar, unsigned int const & version) {

	}
	void save(BO & ar, unsigned int const & version) const {}
	void load(BI & ar, unsigned int const & version) {}
	void save(XO & ar, unsigned int const & version) const {}
	void load(XI & ar, unsigned int const & version) {}
	BOOST_SERIALIZATION_SPLIT_MEMBER();
};


int main()
{
	std::stringstream ss;
	
	XO ar(ss);
	
	foo f;
	
	ar << BOOST_SERIALIZATION_NVP(f);
}




