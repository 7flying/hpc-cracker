PROG=cracker-openmp
SRCS=../hasher/hasher.c ../common/common.c cracker-openmp.c
LINK=-lcrypto -lm -fopenmp

all:
	gcc $(SRCS) -o  $(PROG) $(LINK)


check-syntax:
	gcc -o .nul -S ${CHK_SOURCES}

