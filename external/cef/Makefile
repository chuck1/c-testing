
all:
	g++ -Iinclude -Icef3 -o build/barebones `pkg-config --cflags gtk+-2.0` barebones.cc -Lcef3/bin/linux/x86_64/cef -lcef -lcef_dll_wrapper `pkg-config --libs gtk+-2.0`

