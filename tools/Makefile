
AOS_INFO_OBJECTS=aos-info.o files.o mpk.o
AOS_UNPACK_OBJECTS=aos-unpack.o files.o mpk.o
AOS_FIX_OBJECTS=aos-fix.o files.o mpk.o
AOS_REPACK_OBJECTS=aos-repack.o files.o mpk.o

all: aos-info aos-unpack aos-fix aos-repack

.c.o:
	gcc -c $*.c

aos-info: $(AOS_INFO_OBJECTS)
	gcc -o aos-info $(AOS_INFO_OBJECTS) -L../libaos -laos -lcrypto

aos-unpack: $(AOS_UNPACK_OBJECTS)
	gcc -o aos-unpack $(AOS_UNPACK_OBJECTS) -L../libaos -laos -lcrypto

aos-fix: $(AOS_FIX_OBJECTS)
	gcc -o aos-fix $(AOS_FIX_OBJECTS) -L../libaos -laos -lcrypto

aos-repack: $(AOS_REPACK_OBJECTS)
	gcc -o aos-repack $(AOS_REPACK_OBJECTS) -L../libaos -laos -lcrypto

install:
	cp aos-info /usr/local/bin/
	cp aos-unpack /usr/local/bin/
	cp aos-fix /usr/local/bin/
	cp aos-repack /usr/local/bin/

clean:
	rm -f aos-info aos-unpack aos-fix aos-repack *.o
