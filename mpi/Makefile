PROG=cracker-mpi
SRCS=../hasher/hasher.c ../common/common.c cracker-mpi.c
LINK=-lcrypto -lm
DEBUG_OPS=-h 3 -l 2 -a "0123" -s "936a185caaa266bb9cbe981e9e05cb78cd732b0b3280eb944412bb6f8f8f07af" 


all:
	mpicc $(SRCS) -o $(PROG) $(LINK)

debug:
	mpirun -np 5 ./$(PROG) $(DEBUG_OPS)

check-syntax:
	mpicc -o .nul -S ${CHK_SOURCES}

