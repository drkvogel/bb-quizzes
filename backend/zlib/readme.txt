This directory contains source code for the zlib compression library.

Note that zlib is installed on most linux computers.

For a 32-bit windows library, use c++builder xe4 to build zlibw32.lib using the
project file zlibw32.cbproj . The warnings W8012 (Comparing signed and unsigned
values) and W8071 (Conversion may lose significant digits (C++)) have been
disabled so the library builds cleanly.

For a 64-bit windows library, use c++builder xe4 to build zlibw64.a using the
project file zlibw64.cbproj . The 64-bit compiler does not support disabling
warnings using compiler switches, so all warnings have been disabled so the
library builds cleanly.

For a 64-bit linux library, use gcc 4.1.1 to build zlibl64.a using the makefile
Makefile . The warning for implicit function declarations has been disabled so
the library builds cleanly.

When using the library, the include files zlib.h and zconf.h are also needed.
