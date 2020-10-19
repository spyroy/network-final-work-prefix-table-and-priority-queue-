all: edf bd

edf: edf.c
	gcc -Wall -g edf.c -o edf

bd: bd.c
	gcc -Wall -g bd.c -o bd


.phony: clean all

clean:
	rm -f *.o bd edf
