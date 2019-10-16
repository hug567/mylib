.PHONY : clean

FM=bit.o main.o

main : $(FM)
	gcc -g $^ -o $@
%.c : %.o
	gcc -c -g -Wall $< -o $@
claen :
	rm -rf *.o
