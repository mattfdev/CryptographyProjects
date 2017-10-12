#!/bin/bash
#This program is meant to be run twice, with the specified edits outlined in task5.cpp
echo g++ task5.cpp -o task5 -lcrypt
g++ task5.cpp -o task5 -lcrypt
cd /mnt/unixfiles/crunch-3.6/ #The reason why this is used is because of how crunch is installed on my machine (calling 'crunch ....' does not work). Thus, this line isn't 100% necessary, and the same holds true for line 6. Supposed crunch works better on your machine than mine, this line and line 6 can both be removed.
echo crunch 5 5 abc + 123 -t @@@%% -wordlist.txt
./crunch 5 5 abc + 123 -t @@@%% -o /mnt/unixfiles/school/fall\ 2018/CPS713/lab2/cps713-master/wordlist.txt #This limitation was implemented for complexity purposes.
cd /mnt/unixfiles/school/fall\ 2018/CPS713/lab2/cps713-master
echo Do not enter a previously used username. Enter a password \in\ \(\aaa11,aaa12,.. ,bbb21,...,ccc32,ccc33\). Do not enter a previously used password. 
./task5 1
echo Do not enter a previously used username. Enter a password \in \(\aaa11,aaa12,.. ,bbb21,...,ccc32,ccc33\)\. Do not enter a previously used password.
./task5 1
cat passwd
john --wordlist=wordlist.txt passwd


