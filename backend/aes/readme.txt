This directory contains source code for the aes encryption library.

For a 32-bit windows library, use c++builder xe4 to build aesw32.lib using the
project file aesw32.cbproj . The warning W8056 (Integer arithmetic overflow)
has been disabled so the library builds cleanly.

For a 64-bit windows library, use c++builder xe4 to build aesw64.a using the
project file aesw64.cbproj . The 64-bit compiler does not support disabling
warnings using compiler switches, so all warnings have been disabled so the
library builds cleanly.

For a 64-bit linux library, use gcc 4.1.1 to build aesl64.a using the makefile
Makefile .

When using the library, the include file aes.h is also needed.
