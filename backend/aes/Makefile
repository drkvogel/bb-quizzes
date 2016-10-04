CFLAGS=-Wall -Wextra -pedantic
CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic

LIB=aesl64.a

OBJS= \
aescrypt.o \
aeskey.o \
aestab.o \


default : $(LIB)

$(LIB) : $(LIB)($(OBJS))

clean :
	-rm -f $(OBJS) $(LIB)
