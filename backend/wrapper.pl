#!/usr/bin/perl -w
# cp to e.g. ~/public_html/bbquiz/index.cgi to call e.g. bbquiz.cgi
# for suexec on e.g. xrat but not oqsweb

system('LD_LIBRARY_PATH=/lib:/dbsystem/II/ingres/lib II_SYSTEM=/dbsystem/II ./bbquiz.cgi');
