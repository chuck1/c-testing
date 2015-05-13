
#HPATH = -I/usr/local/cuda-5.5/targets/x86_64-linux/include/
#HPATH = -I/usr/local/cuda-5.5/targets/x86_64-linux/include/

HPATH = -I/usr/include/nvidia-current/
LPATH = -L/usr/lib/nvidia-current/
LIBS = -lOpenCL


all:
	g++ main.cpp -o hello $(HPATH) $(LIBS) -pthread -std=c++0x



