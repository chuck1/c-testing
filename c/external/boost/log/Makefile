

libs += -lboost_system -lboost_thread -lboost_log -lboost_program_options
libs += -lpthread -lrt

defs = -DBOOST_LOG_DYN_LINK

all:
	g++-4.8 main.cpp -o test -std=c++0x ${defs} ${libs}



