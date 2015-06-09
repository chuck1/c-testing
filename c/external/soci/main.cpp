#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <exception>

using namespace soci;
using namespace std;

bool get_name(string &name)
{
	cout << "Enter name: ";
	return cin >> name;
}

int main()
{
	try
	{
		session sql(mysql, "host=oniddb.cws.oregonstate.edu dbname=rymalc-db user=rymalc-db password='HIJGYGHHGCWXieGl'");

		int count;
		sql << "select count(*) from phonebook", into(count);

		cout << "We have " << count << " entries in the phonebook.\n";

		string name;
		while (get_name(name))
		{
			string phone;
			indicator ind;
			sql << "select phone from phonebook where name = :name",
			    into(phone, ind), use(name);

			if (ind == i_ok)
			{
				cout << "The phone number is " << phone << '\n';
			}
			else
			{
				cout << "There is no phone for " << name << '\n';
			}
		}
	}
	catch (exception const &e)
	{
		cerr << "Error: " << e.what() << '\n';
	}
}

