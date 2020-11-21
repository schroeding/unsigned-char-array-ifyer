ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: 
	gcc main.c -o uca

windows:
	x86_64-w64-mingw32-gcc main.c -o uca.exe

clean:
	rm uca.exe
	rm uca

install:
	cp uca $(DESTDIR)$(PREFIX)/bin/uca
	chmod 755 $(DESTDIR)$(PREFIX)/bin/uca

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/uca