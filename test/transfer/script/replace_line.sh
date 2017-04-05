#!/bin/bash

foo="bar"

printf "hello world\nli_ne to replace\ngoodbye\n" > t1

cat t1

sed "s/li_ne.*/bingo $foo/" t1 > t2

cat t2



perl -pe "s/li_ne.*/bingo $foo/" t1 > t3

cat t3

printf "$PWD\n" > t4

cat t4

perl -pe "s/\//1/g" t4 > t5

cat t5
