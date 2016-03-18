PROG=cracker-seq
SRCS=hasher.c cracker-seq.c
LINK=-lcrypto

all:
	gcc $(SRCS) -o  $(PROG) $(LINK)


check-syntax:
	gcc -o .nul -S ${CHK_SOURCES}

