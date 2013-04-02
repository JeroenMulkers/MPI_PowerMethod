COMP = mpicc -std=c99
OBJS = main.o matrix.o matrix_test.o

main.out: $(OBJS)
	$(COMP) $^ -o $@ -lm

%.o: %.c *.h
	$(COMP) -c $<

.PHONY: clean realclean

clean:
	rm -f *.o

realclean: clean
	rm -f *.out
	rm *.dat
