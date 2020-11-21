ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: 
	gcc main.c -o uca

clean:
	rm uca

install:
	cp uca $(DESTDIR)$(PREFIX)/bin/uca
	chmod 755 $(DESTDIR)$(PREFIX)/bin/uca

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/uca