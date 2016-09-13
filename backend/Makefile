CCXXFLAGS=-Dint_lnx -g
CXX=g++
SHELL=/bin/sh
INC=$(II_SYSTEM)/ingres/files
LDLIB=-linterp.1 -liiapi 
CXXFLAGS=$(CCXXFLAGS) -I$(INC)
OBJS= rosebase.o rosetta.o \
    xbinob.o xdb.o xencode.o xexec.o xquery.o xsql.o xtime.o xhttp.o xcgi.o \
	hoops.o matrix.o nxjson.o

bbquiz : bbquiz.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o bbquiz.cgi bbquiz.cpp $(OBJS) -L$(II_SYSTEM)/ingres/lib -lingres $(LDLIB)
	chmod go-w bbquiz.cgi
	cp bbquiz.cgi ~cp/public_html/bbquiz/

clean :
	rm *.o

# test : test.o
# 	$(CXX) $(CXXFLAGS) -o test test.cpp $(OBJS) -L$(II_SYSTEM)/ingres/lib -lingres $(LDLIB)

# send_single : send_single.o $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o send_single send_single.cpp $(OBJS) -L$(II_SYSTEM)/ingres/lib -lingres $(LDLIB)

# websms : websms.o $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o websms websms.cpp $(OBJS) -L$(II_SYSTEM)/ingres/lib -lingres $(LDLIB)
	#cp /user/webman/public_html/sendsms/index.cgi /user/webman/public_html/sendsms/index.cgi.bak
	#cp websms /user/webman/public_html/sendsms/index.cgi
