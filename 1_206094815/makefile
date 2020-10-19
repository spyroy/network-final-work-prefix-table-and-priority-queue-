all: prefix_table prefix_table_opt

prefix_table: prefix_table.c
	gcc -Wall -g prefix_table.c -o prefix_table

prefix_table_opt: prefix_table_opt.c
	gcc -Wall -g prefix_table_opt.c -o prefix_table_opt


.phony: clean all

clean:
	rm -f *.o prefix_table prefix_table_opt
