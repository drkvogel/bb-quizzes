CFLAGS=-Wall -Wextra -pedantic
CFLAGS+= -Wno-implicit-function-declaration
CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic
CXXFLAGS+= -Wno-implicit-function-declaration

LIB=zlibl64.a

OBJS= \
adler32.o \
compress.o \
crc32.o \
deflate.o \
gzclose.o \
gzlib.o \
gzread.o \
gzwrite.o \
infback.o \
inffast.o \
inflate.o \
inftrees.o \
trees.o \
uncompr.o \
zutil.o \


default : $(LIB)

$(LIB) : $(LIB)($(OBJS))

clean :
	-rm -f $(OBJS) $(LIB)
