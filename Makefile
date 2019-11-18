
C=gcc
RM=rm -f
#CFLAGS=-w -O3 -march=native -funroll-all-loops -fomit-frame-pointer
CFLAGS=-Wall -Wextra -Wpedantic -O3 -march=native -funroll-all-loops -fomit-frame-pointer -Wint-conversion
SRCS=main.c haraka.c
OBJS=$(subst .c,.o,$(SRCS))
OUTFILE="./haraka"

all: haraka

haraka: $(OBJS)
	$(C) -o $(OUTFILE) $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(C) $(CFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend

