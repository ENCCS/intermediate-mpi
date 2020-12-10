# -*- Mode: Makefile; -*-
#
# See COPYRIGHT in top-level directory.
#

CC=mpicc
CFLAGS= -g -Wall -std=c11
BINS=collective-communication-broadcast

#all: $(BINS)

collective-communication-broadcast: collective-communication-broadcast.c
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean:
	rm -f $(BINS)
	rm -f output*.bmp
