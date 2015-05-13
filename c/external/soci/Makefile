INCLUDE_DIRS =  -I/scratch/usr/include/soci/
INCLUDE_DIRS += -I/scratch/mysql-connector-c-6.1.5-linux-glibc2.5-x86_64/include

LIBS = -lsoci_mysql

all:
	g++ main.cpp -o test ${INCLUDE_DIRS} ${LIBS}
