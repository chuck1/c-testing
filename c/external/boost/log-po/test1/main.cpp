

/*
 *  *          Copyright Andrey Semashev 2007 - 2013.
 *   * Distributed under the Boost Software License, Version 1.0.
 *    *    (See accompanying file LICENSE_1_0.txt or copy at
 *     *          http://www.boost.org/LICENSE_1_0.txt)
 *      */

#include <cstddef>
#include <iostream>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#if 0 
#include <boost/program_options.hpp>

namespace po = boost::program_options;
#endif




namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

//[ example_expressions_channel_severity_filter
// We define our own severity levels
enum severity_level
{
	normal,
	notification,
	warning,
	error,
	critical
};

// Define the attribute keywords
BOOST_LOG_ATTRIBUTE_KEYWORD(line_id, "LineID", unsigned int)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(channel, "Channel", std::string)

//<-
std::ostream& operator<< (std::ostream& strm, severity_level level)
{
	static const char* strings[] =
	{
		"normal",
		"notification",
		"warning",
		"error",
		"critical"
	};

	if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
		strm << strings[level];
	else
		strm << static_cast< int >(level);

	return strm;
}


typedef expr::channel_severity_filter_actor< std::string, severity_level > min_severity_filter;
min_severity_filter min_severity = expr::channel_severity_filter(channel, severity);

void init()
{
	// Create a minimal severity table filter

	// Set up the minimum severity levels for different channels

	logging::add_console_log
		(
		 std::clog,
		 keywords::filter = min_severity || severity >= critical,
		 keywords::format =
		 (
		  expr::stream
		  << line_id
		  << ": <" << severity
		  << "> [" << channel << "] "
		  << expr::smessage
		 )
		);
}

// Define our logger type
typedef src::severity_channel_logger< severity_level, std::string > logger_type;

void test_logging(logger_type& lg, std::string const& channel_name)
{
	BOOST_LOG_CHANNEL_SEV(lg, channel_name, normal) << "A normal severity level message";
	BOOST_LOG_CHANNEL_SEV(lg, channel_name, notification) << "A notification severity level message";
	BOOST_LOG_CHANNEL_SEV(lg, channel_name, warning) << "A warning severity level message";
	BOOST_LOG_CHANNEL_SEV(lg, channel_name, error) << "An error severity level message";
	BOOST_LOG_CHANNEL_SEV(lg, channel_name, critical) << "A critical severity level message";
}
//]


int main(int ac, char** av) {

#if 0
	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("compression", po::value<int>(), "set compression level")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);
	po::notify(vm);    

	if (vm.count("help")) {
		std::cout << desc << "\n";
		return 1;
	}

	if (vm.count("compression")) {
		std::cout << "Compression level was set to " 
			<< vm["compression"].as<int>() << ".\n";
	} else {
		std::cout << "Compression level was not set.\n";
	}
}
#endif

// logging
logging::add_common_attributes();
init();

min_severity["general"] = notification;
min_severity["network"] = warning;
min_severity["gui"] = error;

logger_type lg;
test_logging(lg, "general");
test_logging(lg, "network");
test_logging(lg, "gui");
test_logging(lg, "filesystem");


return 0;

}







