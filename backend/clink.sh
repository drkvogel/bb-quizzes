#!/bin/bash

if [$1 == '']
then
    FILE_BASE="bbquiz"
    #echo no filename base supplied, using $FILE_BASE
else
    FILE_BASE=$1
    #echo using $FILE_BASE as filename base
fi

echo "use cci bbquiz.cpp and rename a.out to bbquiz"
echo "use cci -g and gdb to debug (file a.out, break <breakpoint>, run, step/next)"

#gcc -c "$FILE_BASE".c -o "$FILE_BASE"_out

#cp "$FILE_BASE"_out "$WEB_ROOT/$FILE_BASE.cgi"
#chmod 755 "$WEB_ROOT/$FILE_BASE.cgi"
