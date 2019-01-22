GCC = g++
CPPFLAGS = -pedantic -ggdb3 -Wall -Werror
SRCS = $(wildcard *.cpp)
search: search.o bsearch.o
	$(GCC) $(CPPFLAGS) -o search search.o bsearch.o
%.o:%.cpp
	$(GCC) $(CPPFLAGS) -c $<

.PHONY: clean depend

clean:
	rm -f search *.o *~
depend:
	makedepend $(SRCS)

#DO NOT DELETE
