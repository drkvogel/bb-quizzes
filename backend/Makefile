SHELL=/bin/sh
CXX=g++
CCXXFLAGS=-Dint_lnx -g
INC=$(II_SYSTEM)/ingres/files
LDLIB=-linterp.1 -liiapi 
CXXFLAGS=$(CCXXFLAGS) -I$(INC)
OBJCOMMON=rosebase.o rosetta.o xbinob.o xdb.o xencode.o xexec.o xquery.o xsql.o xtime.o xhttp.o xcgi.o
OBJBBQUIZ=$(OBJCOMMON) hoops.o matrix.o nxjson.o
TARGETDIR=~cp/public_html/bbquiz/

bbquiz : bbquiz.o $(OBJBBQUIZ)
	echo "make bbquiz"
	$(CXX) $(CXXFLAGS) -o bbquiz.cgi bbquiz.cpp $(OBJBBQUIZ) -L$(II_SYSTEM)/ingres/lib -lingres $(LDLIB)
	chmod go-w bbquiz.cgi
	cp bbquiz.cgi $(TARGETDIR)
	cp main.css $(TARGETDIR)

nodb : bbquiz.o $(OBJBBQUIZ)
	echo "make nodb"
	$(CXX) $(CCXXFLAGS) -o index.cgi bbquiz.cpp $(OBJBBQUIZ)

#chmod go-w bbquiz.cgi
#cp bbquiz.cgi $(TARGETDIR)
#cp main.css $(TARGETDIR)

idserve: idserve.o $(OBJCOMMON)
	$(CXX) $(CXXFLAGS) -o idserve.cgi idserve.cpp $(OBJCOMMON) -L$(II_SYSTEM)/ingres/lib -lingres $(LDLIB)
	chmod go-w idserve.cgi
	cp idserve.cgi $(TARGETDIR)

clean :
	echo "make clean"
	rm *.o

# test : test.o
# 	$(CXX) $(CXXFLAGS) -o test test.cpp $(OBJS) -L$(II_SYSTEM)/ingres/lib -lingres $(LDLIB)

# send_single : send_single.o $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o send_single send_single.cpp $(OBJS) -L$(II_SYSTEM)/ingres/lib -lingres $(LDLIB)

# websms : websms.o $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o websms websms.cpp $(OBJS) -L$(II_SYSTEM)/ingres/lib -lingres $(LDLIB)
	#cp /user/webman/public_html/sendsms/index.cgi /user/webman/public_html/sendsms/index.cgi.bak
	#cp websms /user/webman/public_html/sendsms/index.cgi

# \ to span lines, e.g.
# OBJS= rosebase.o rosetta.o \
#     xbinob.o xdb.o xencode.o xexec.o xquery.o xsql.o xtime.o xhttp.o xcgi.o
