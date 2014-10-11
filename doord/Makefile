#
# Makefile for doord and doorcontrol
#
# written by Aaron Solochek <aarons@aberrant.org>
# last modified: 8 May 2003
#

SHELL		= /bin/sh
CC		= gcc
INSTALL 	= /usr/bin/install -c
LIBS 		= 
INC		= -I.
CFLAGS 		= -g -Wall 
ARGS		=

prefix		= /usr/local
bindir		= ${prefix}/bin
transform	= s,x,x,

SOURCES 	= main.c  init.c leddisp.c
OBJS		= global.o init.o leddisp.o
M_OBJS		= doord.o ledtest.o
PROGS		= doord

all: doord

install: all
	for x in $(PROGS); do \
	$(INSTALL) -g rc99 -o rc99 -m 4775 $$x $(DESTDIR)$(bindir)/`echo $$x | sed '$(transform)'`; \
	done

uninstall:
	for x in $(PROGS); do \
	rm -f $(DESTDIR)$(bindir)/`echo $$x | sed '$(transform)'`; \
	done

doord: $(OBJS) doord.o
	$(CC) $(CFLAGS) $(ARGS) $(INC) $(OBJS) doord.o -o doord $(LIBS)

ledtest: $(OBJS) ledtest.o
	$(CC) $(CFLAGS) $(ARGS) $(INC) $(OBJS) ledtest.o -o ledtest $(LIBS)

ledtest.o: ledtest.c
	$(CC) $(CFLAGS) $(ARGS) $(INC) -c ledtest.c

global.o: global.c
	$(CC) $(CFLAGS) $(ARGS) $(INC) -c global.c

doord.o: doord.c
	$(CC) $(CFLAGS) $(ARGS) $(INC) -c doord.c

genfuns.o: genfuns.c 
	$(CC) $(CFLAGS) $(ARGS) $(INC) -c genfuns.c

init.o: init.c
	$(CC) $(CFLAGS) $(ARGS) $(INC) -c init.c

io.o: io.c 
	$(CC) $(CFLAGS) $(ARGS) $(INC) -c io.c

leddisp.o: leddisp.c
	$(CC) $(CFLAGS) $(ARGS) $(INC) -c leddisp.c

clean: 
	-rm -f $(PROGS) $(OBJS) $(M_OBJS) ledtest

allclean:
	-rm -f *.o *~ $(PROGS)

backclean:
	-rm *~

