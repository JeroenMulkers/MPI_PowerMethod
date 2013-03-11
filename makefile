COMP = mpicc -std=c99
OBJS = main.o matrix.o

main.out: $(OBJS)
	$(COMP) $^ -o $@

%.o: %.c *.h
	$(COMP) -c $<

.PHONY: clean realclean

clean:
	rm -f *.o

realclean: clean
	rm -f *.out
