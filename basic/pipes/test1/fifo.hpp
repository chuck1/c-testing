#ifndef MY_FIFO
#define MY_FIFO

int pipe_write(char const* data_out, int len);
int pipe_read(char * buf, int len);

#endif


