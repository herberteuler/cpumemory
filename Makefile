
CFLAGS += -DCLS=$$(getconf LEVEL1_DCACHE_LINESIZE) -std=c99

all:	matrix1 matrix2 matrix3 l1acc

matrix1:	matrix1.o
	$(CC) $(CFLAGS) -o matrix1 $(^)

matrix2:	matrix2.o
	$(CC) $(CFLAGS) -o matrix2 $(^)

matrix3:	matrix3.o
	$(CC) $(CFLAGS) -o matrix3 $(^)

matrix1.o matrix2.o matrix3.o:	matrix.h

l1acc:	l1acc.o
	$(CC) $(CFLAGS) -o l1acc $(^)

.PHONY:	clean
clean:
	$(RM) *.o

.PHONY:	distclean
distclean:	clean
	$(RM) matrix1 matrix2 matrix3 l1acc
