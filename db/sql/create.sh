#!/bin/tcsh
cd ~/Projects/bb-quizzes/db/sql

#set end = $argv[1]
set end = 'test'
set own = 'cp_web_'
set xdb = ( $own$end )

destroydb $xdb
createdb -i $xdb

sql $xdb < hoops.sql
#sql $xdb < matrix.sql

#! /bin/sh

sql iidbdb << GRANTED
grant access on database cp_web_test to cp;
\p\g
\q
GRANTED