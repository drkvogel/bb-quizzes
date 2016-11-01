SHELL=/bin/sh
CXX=g++
CCXXFLAGS=-Dint_lnx -g
INC=$(II_SYSTEM)/ingres/files
LDLIB=-linterp.1 -liiapi /lib64/libdl.so.2 /lib64/libcrypt.so.1 
CXXFLAGS=$(CCXXFLAGS) -I$(INC)
OBJCOMMON=rosebase.o rosetta.o xbinob.o xdb.o xencode.o xexec.o xquery.o xsql.o xtime.o xcgi.o xerror.o
OBJBBQUIZ=$(OBJCOMMON) nxjson.o hoops.o matrix.o
TARGETDIR=~/public_html/bbquiz/

bbquiz : bbquiz.o $(OBJBBQUIZ)
	echo "make bbquiz"
	$(CXX) $(CXXFLAGS) -o bbquiz.cgi bbquiz.cpp $(OBJBBQUIZ) -L$(II_SYSTEM)/ingres/lib -lingres $(LDLIB)
	chmod go-w bbquiz.cgi
	#cp bbquiz.cgi $(TARGETDIR)index.cgi
	#cp main.css $(TARGETDIR)
	scp bbquiz.cgi cp@oqsweb:~/public_html/bbquiz/index.cgi
	scp main.css cp@oqsweb:~/public_html/bbquiz/

nodb : bbquiz.o $(OBJBBQUIZ)
	echo "make nodb"
	$(CXX) $(CCXXFLAGS) -DNO_INGRES -o index.cgi bbquiz.cpp $(OBJBBQUIZ)

#chmod go-w bbquiz.cgi
#cp bbquiz.cgi $(TARGETDIR)
#cp main.css $(TARGETDIR)

# idserve: idserve.o $(OBJCOMMON)
# 	$(CXX) $(CXXFLAGS) -o idserve.cgi idserve.cpp $(OBJCOMMON) -L$(II_SYSTEM)/ingres/lib -lingres $(LDLIB)
# 	chmod go-w idserve.cgi
# 	cp idserve.cgi $(TARGETDIR)

clean :
	echo "make clean"
	rm *.o

# \ to span lines, e.g.
# OBJS= rosebase.o rosetta.o \
#     xbinob.o xdb.o xencode.o xexec.o xquery.o xsql.o xtime.o xhttp.o xcgi.o
