#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "fifo.hpp"

int main()
{
	pipe_write("hello", 5);
}

