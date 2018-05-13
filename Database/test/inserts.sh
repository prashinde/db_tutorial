#!/bin/bash

PRG=../bin/database
DBFILE=../bin/dfile
MFILE=../bin/metafile
QUERY=insert

rm -rf $DBFILE $MFILE

touch $DBFILE $MFILE

nrecs=$1

while [ $nrecs -gt 0 ];
do
	record=$(cat /dev/urandom | tr -dc 'a-zA-Z' | fold -w 10 | head -n 3)
	$PRG $DBFILE $MFILE $((RANDOM)) 0  "\""$QUERY $record"\""
	(( nrecs-- ))
done
