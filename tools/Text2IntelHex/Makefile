CC = gcc
	
.PHONY : build
build : text2intelhex.c
	$(CC) -c text2intelhex.c -o text2intelhex.o
	$(CC) text2intelhex.o -o text2intelhex
	rm *.o
	
.PHONY: clean
clean: 
	rm -r build

print-%  : ; @echo $* = $($*)
