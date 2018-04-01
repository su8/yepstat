CFLAGS+=-Wall -Wextra -O2 -D_POSIX_C_SOURCE=200112L
SRCS=yepstat.c print2.c
PROGS=yepstat print2

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

install: 
	install -D -s -m 755 yepstat /usr/bin/yepstat
	install -D -s -m 755 print2 /usr/bin/print2

clean:
	rm -f /usr/bin/yepstat
	rm -f /usr/bin/print2

.PHONY: all install clean
