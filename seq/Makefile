PROG=cracker-seq
SRCS=../hasher/hasher.c ../common/common.c cracker-seq.c
LINK=-lcrypto -lm

all:
	gcc $(SRCS) -o  $(PROG) $(LINK)


check-syntax:
	gcc -o .nul -S ${CHK_SOURCES}

