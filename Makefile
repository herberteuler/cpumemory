
# These variables are used in `acc.c'.
ACC_NPAD ?= 7

CFLAGS += -DACC_NPAD=$(ACC_NPAD) \
	  -DCLS=$$(getconf LEVEL1_DCACHE_LINESIZE) \
	  -std=c99 -Wall

all:	matrix1 matrix2 matrix3 acc

matrix1:	matrix1.o driver.o
	$(CC) $(CFLAGS) -o matrix1 $(^)

matrix2:	matrix2.o driver.o
	$(CC) $(CFLAGS) -o matrix2 $(^)

matrix3:	matrix3.o driver.o
	$(CC) $(CFLAGS) -o matrix3 $(^)

matrix1.o matrix2.o matrix3.o:	matrix.h

acc:	acc.o driver.o
	$(CC) $(CFLAGS) -o acc $(^)

.PHONY:	clean
clean:
	$(RM) *.o

.PHONY:	distclean
distclean:	clean
	$(RM) matrix1 matrix2 matrix3 acc
