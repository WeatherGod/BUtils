CC = gcc
VERSION = 0.9

# if the system does not support file locking,
# then define the macro _NO_FILELOCK by uncommenting below
DEFFLAGS = -D _DOLINKING_ # -D _NO_FILELOCK


BOBJECTS = VectorUtly.o StrUtly.o ConfigUtly.o FlockUtly.o TimeUtly.o FormatUtly.o CmdLineUtly.o DistUtly.o StatUtly.o Histogram.o

#################################################################################
MYINC_PATH = /usr/include/BUtils
MYLIB_PATH = /usr/lib
################################################################################

all : BUtils

BUtils : libBUtils.so

libBUtils.so : lib/libBUtils.so

lib/libBUtils.so : $(BOBJECTS)
	$(CC) $(LDFLAGS) -shared $(BOBJECTS) -o lib/libBUtils.so -l stdc++



# --------------------------------- BUtils -----------------------------------------
VectorUtly.o : include/VectorUtly.h src/VectorUtly.C
	$(CC) -fPIC -c src/VectorUtly.C -o VectorUtly.o $(DEFFLAGS) -I include/

StrUtly.o : include/StrUtly.h src/StrUtly.C
	$(CC) -fPIC -c src/StrUtly.C -o StrUtly.o $(DEFFLAGS) -I include/

ConfigUtly.o : include/ConfigUtly.h src/ConfigUtly.C
	$(CC) -fPIC -c src/ConfigUtly.C -o ConfigUtly.o $(DEFFLAGS) -I include/

FlockUtly.o : include/FlockUtly.h src/FlockUtly.C
	$(CC) -fPIC -c src/FlockUtly.C -o FlockUtly.o $(DEFFLAGS) -I include/

TimeUtly.o : include/TimeUtly.h src/TimeUtly.C
	$(CC) -fPIC -c src/TimeUtly.C -o TimeUtly.o $(DEFFLAGS) -I include/

FormatUtly.o : include/FormatUtly.h src/FormatUtly.C
	$(CC) -fPIC -c src/FormatUtly.C -o FormatUtly.o $(DEFFLAGS) -I include/

CmdLineUtly.o : include/CmdLineUtly.h src/CmdLineUtly.C
	$(CC) -fPIC -c src/CmdLineUtly.C -o CmdLineUtly.o $(DEFFLAGS) -I include/

DistUtly.o : include/DistUtly.h src/DistUtly.C
	$(CC) -fPIC -c src/DistUtly.C -o DistUtly.o $(DEFFLAGS) -I include/

StatUtly.o : include/StatUtly.h src/StatUtly.C
	$(CC) -fPIC -c src/StatUtly.C -o StatUtly.o $(DEFFLAGS) -I include/

Histogram.o : include/Histogram.h src/Histogram.C
	$(CC) -fPIC -c src/Histogram.C -o Histogram.o $(DEFFLAGS) -I include/
#--------------------------------------------------------------------------------


install : $(MYINC_PATH)/VectorUtly.h $(MYINC_PATH)/StrUtly.h $(MYINC_PATH)/ConfigUtly.h \
          $(MYINC_PATH)/FlockUtly.h $(MYINC_PATH)/TimeUtly.h $(MYINC_PATH)/FormatUtly.h \
          $(MYINC_PATH)/CmdLineUtly.h $(MYINC_PATH)/DistUtly.h $(MYINC_PATH)/StatUtly.h \
          $(MYINC_PATH)/Histogram.h \
          $(MYLIB_PATH)/libBUtils.so

# ---------------------------- BUtils -----------------------------------------
$(MYINC_PATH)/VectorUtly.h : include/VectorUtly.h
	cp -f include/VectorUtly.h $(MYINC_PATH)/VectorUtly.h

$(MYINC_PATH)/StrUtly.h : include/StrUtly.h
	cp -f include/StrUtly.h $(MYINC_PATH)/StrUtly.h

$(MYINC_PATH)/ConfigUtly.h : include/ConfigUtly.h
	cp -f include/ConfigUtly.h $(MYINC_PATH)/ConfigUtly.h

$(MYINC_PATH)/FlockUtly.h : include/FlockUtly.h
	cp -f include/FlockUtly.h $(MYINC_PATH)/FlockUtly.h

$(MYINC_PATH)/TimeUtly.h : include/TimeUtly.h
	cp -f include/TimeUtly.h $(MYINC_PATH)/TimeUtly.h

$(MYINC_PATH)/FormatUtly.h : include/FormatUtly.h
	cp -f include/FormatUtly.h $(MYINC_PATH)/FormatUtly.h

$(MYINC_PATH)/CmdLineUtly.h : include/CmdLineUtly.h
	cp -f include/CmdLineUtly.h $(MYINC_PATH)/CmdLineUtly.h

$(MYINC_PATH)/DistUtly.h : include/DistUtly.h
	cp -f include/DistUtly.h $(MYINC_PATH)/DistUtly.h

$(MYINC_PATH)/StatUtly.h : include/StatUtly.h
	cp -f include/StatUtly.h $(MYINC_PATH)/StatUtly.h

$(MYINC_PATH)/Histogram.h : include/Histogram.h
	cp -f include/Histogram.h $(MYINC_PATH)/Histogram.h

$(MYLIB_PATH)/libBUtils.so : lib/libBUtils.so
	cp -f lib/libBUtils.so $(MYLIB_PATH)/libBUtils.so
#---------------------------------------------------------------------------


clean :
	- rm -f "BUtils-$(VERSION).tar"
	- rm -f "BUtils-$(VERSION).tar.gz"
	- rm -f "BUtils-$(VERSION).tar.bz2"
	- rm -f $(BOBJECTS)
	- rm -f lib/libBUtils.so

uninstall : remove

remove :
	- rm -f $(MYINC_PATH)/VectorUtly.h
	- rm -f $(MYINC_PATH)/StrUtly.h
	- rm -f $(MYINC_PATH)/ConfigUtly.h
	- rm -f $(MYINC_PATH)/FlockUtly.h
	- rm -f $(MYINC_PATH)/TimeUtly.h
	- rm -f $(MYINC_PATH)/FormatUtly.h
	- rm -f $(MYINC_PATH)/CmdLineUtly.h
	- rm -f $(MYINC_PATH)/DistUtly.h
	- rm -f $(MYINC_PATH)/StatUtly.h
	- rm -f $(MYINC_PATH)/Histogram.h
	- rm -f $(MYLIB_PATH)/libBUtils.so

tar : BUtils-$(VERSION).tar

tar.gz : BUtils-$(VERSION).tar.gz

tar.bz2 : BUtils-$(VERSION).tar.bz2

BUtils-$(VERSION).tar.gz : BUtils-$(VERSION).tar
	gzip -f "BUtils-$(VERSION).tar"

BUtils-$(VERSION).tar.bz2 : BUtils-$(VERSION).tar
	bzip2 -f "BUtils-$(VERSION).tar"

BUtils-$(VERSION).tar : include/VectorUtly.h include/StrUtly.h include/ConfigUtly.h include/FlockUtly.h \
             include/TimeUtly.h include/FormatUtly.h include/CmdLineUtly.h include/DistUtly.h \
             include/StatUtly.h include/Histogram.h \
             src/VectorUtly.C src/StrUtly.C src/ConfigUtly.C src/FlockUtly.C \
             src/TimeUtly.C src/FormatUtly.C src/CmdLineUtly.C src/DistUtly.C \
             src/StatUtly.C src/Histogram.C \
             Makefile
	mkdir -p "BUtils-$(VERSION)/include"
	mkdir -p "BUtils-$(VERSION)/src"
	mkdir -p "BUtils-$(VERSION)/lib"
	cp -f include/VectorUtly.h include/StrUtly.h include/ConfigUtly.h include/FlockUtly.h \
              include/TimeUtly.h include/FormatUtly.h include/CmdLineUtly.h include/DistUtly.h \
              include/StatUtly.h include/Histogram.h "BUtils-$(VERSION)/include"
	cp -f src/VectorUtly.C src/StrUtly.C src/ConfigUtly.C src/FlockUtly.C \
              src/TimeUtly.C src/FormatUtly.C src/CmdLineUtly.C src/DistUtly.C \
              src/StatUtly.C src/Histogram.C "BUtils-$(VERSION)/src"
	cp -f Makefile "BUtils-$(VERSION)/"
	-rm -f "BUtils-$(VERSION).tar"
	tar -cf "BUtils-$(VERSION).tar" "BUtils-$(VERSION)/"
	rm -rf "BUtils-$(VERSION)/"
