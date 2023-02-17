# tily - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c tily.c util.c
OBJ = ${SRC:.c=.o}

all: options tily

options:
	@echo tily build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

tily: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f tily ${OBJ} tily-${VERSION}.tar.gz

dist: clean
	mkdir -p tily-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		tily.1 drw.h util.h ${SRC} tily.png transient.c tily-${VERSION}
	tar -cf tily-${VERSION}.tar tily-${VERSION}
	gzip tily-${VERSION}.tar
	rm -rf tily-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f tily ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/tily
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < tily.1 > ${DESTDIR}${MANPREFIX}/man1/tily.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/tily.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/tily\
		${DESTDIR}${MANPREFIX}/man1/tily.1

.PHONY: all options clean dist install uninstall
