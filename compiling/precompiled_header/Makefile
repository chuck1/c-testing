PCH = gcc -c -x c-header

a.out: main.o
	gcc -o $@ $<

pre.h.gch: pre.h
	$(PCH) $< -o $@

main.o: main.c pre.h.gch
	gcc -c $< -o $@

clean:
	rm -f a.out main.o pre.h.gch
