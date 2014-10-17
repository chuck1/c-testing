#include <sstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

int main(int ac, char ** av) {

	// RAII cleanup
	curlpp::Cleanup myCleanup;

	// standard request object.
	curlpp::Easy myRequest;

	std::ostringstream os;
	
	
	//std::string url("http://www.wikipedia.org");
	//std::string url("http://people.oregonstate.edu/~rymalc/");
	//std::string url("http://people.oregonstate.edu/~rymalc/test/post/post.php");
	//std::string url("http://people.oregonstate.edu/~rymalc/test/");
	//std::string url("http://people.oregonstate.edu/~rymalc/test/test.py");
	//std::string url(av[1]);

	std::string url("http://www.corvallistransit.com/rtt/public/utility/file.aspx?contenttype=SQLXML&Name=RoutePositionET.xml&PlatformTag=145");

	// Set the URL.
	myRequest.setOpt(new curlpp::options::Url(url));



	std::string test = "hello=1"; 
	//myRequest.setOpt(new curlpp::options::PostFields(test)); 
	//myRequest.setOpt(new curlpp::options::PostFieldSize(test.length()));



	myRequest.setOpt(new curlpp::options::WriteStream( &os ));

	// Send request and get a result.
	// By default the result goes to standard output.
	// Here I use a shortcut to get it in a string stream ...
	/*os <<*/ myRequest.perform();



	std::string asAskedInQuestion = os.str();

	std::cout << asAskedInQuestion << std::endl;
}

