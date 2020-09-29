CC = gcc
objects = main.o main_list.o main_bitmap.o main_hash.o list.o bitmap.o hash.o hex_dump.o debug.o

testlib		:	$(objects)
	$(CC) -o testlib $(objects)

clean : 
	rm -rf $(objects) testlib
	
	