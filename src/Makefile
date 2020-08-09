CFLAGS = -g

all: tester main

history.o: history.h
tokenizer.o: tokenizer.h
main.o: tokenizer.h history.h
tester.o: tokenizer.h history.h

tester: history.o tokenizer.o tester.o
	cc -o $@ $^ $(CFLAGS)

main: history.o tokenizer.o main.o

clean:
	rm -f *.o tester main
