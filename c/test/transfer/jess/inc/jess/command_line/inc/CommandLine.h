#ifndef _COMMANDLINE_H
#define _COMMANDLINE_H

/// Container for command-line arguments.
/// This class assumes argument 0 is always the executable path!
class CommandLine {
public:
	/// Constructor
								CommandLine( unsigned int argc, const char*const* argv );
	/// Constructor
								CommandLine( const char* args );
	/// Destructor
								~CommandLine();
	/// Copy Constructor
								CommandLine( const CommandLine& );
	/// Default Constructor
								CommandLine();
		
	
	/// Assignment
				CommandLine		operator=( const CommandLine& );

	/// has a given command-line switch?
	/** e.g. s=="foo" checks for -foo */
	bool			has_switch( const char* s, const unsigned int argNum = invalidArgNum ) const;

	/// gets the value of a switch.
	/// e.g. s="foo" returns "bar" if '-foo=bar' is in the commandline.
	const char*		get_value( const char* s, unsigned int argNum = invalidArgNum ) const;

	/// return how many command line arguments there are
	unsigned int		get_argc() const;

	/// what is the program name
	const char*		get_program_name() const;

	/// get the string that contains the unsued args
	unsigned int		unused_args_buf_size() const;

	/// get the string that contains the unsued args
	const char*		getUnusedArgs( char* buf, unsigned int bufSize ) const;

	/// if the first argument is the given command.
	bool			isCommand( const char* s ) const;

	///! get the first argument assuming it isn't a switch.
	///  e.g. for the command-line "myapp.exe editor -foo" it will return "editor".
	const		char*			getCommand() const;

	/// get the raw command-line argument list...
	unsigned	int				getArgC() const { return m_argc; }
	/// get the raw command-line argument list...
	const		char*const*		getArgV() const { return m_argv; }

private:
	/// number of arguments
	unsigned	int				m_argc;
	/// charactor string
	const		char* const*	m_argv;
	/// unknown
				void*			m_freeme;
	/// unknown
	static const unsigned int	invalidArgNum = 0xFFFFFFFFU;
	/// unknown
				bool*			m_argUsed;
};



char**	CommandLineToArgvA( const char *cmdLine, unsigned int &_argc );
bool	isSwitchChar( char c );


#endif



