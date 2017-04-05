dot_files = doc/graph.dot
png_files = $(patsubst %.dot,build/%.png,$(dot_files))

all: build/test

doc: $(png_files)

root = $(shell pwd)

c_files_a = src/A/foo.cpp
o_files_a = $(patsubst %.cpp,build/%.o,$(c_files_a))
c_files_b = src/B/foo.cpp
o_files_b = $(patsubst %.cpp,build/%.o,$(c_files_b))

$(png_files): build/%.png: %.dot
	@mkdir $(dir $@) -p
	@dot $< -Tpng -o$@

$(o_files_a) $(o_files_b): build/%.o: %.cpp
	@mkdir $(dir $@) -p
	g++ -Wall -fPIC -c $< -o $@ -I.

build/libA.so: $(o_files_a)
	@mkdir $(dir $@) -p
	g++ -shared -Wl,-soname,$@.1 -o $@.1.0 $(o_files_a)
	ln -sf $(root)/$@.1.0 $(root)/$@.1
	ln -sf $(root)/$@.1.0 $(root)/$@

build/libB.so: $(o_files_b)
	@mkdir $(dir $@) -p
	g++ -shared -Wl,-soname,$@.1 -o $@.1.0 $(o_files_b)
	ln -sf $(root)/$@.1.0 $(root)/$@.1
	ln -sf $(root)/$@.1.0 $(root)/$@

build/test: build/libA.so build/libB.so
	g++ src/test/main.cpp -o $@ -I. -Lbuild -lA -lB

clean:
	rm -rf build

