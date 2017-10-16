#!/bin/bash
#This program is meant to be run twice, with the specified edits outlined in task5.cpp
#echo g++ task5.cpp -o task5 -lcrypt (Uncomment line below if johnTester.sh fails to work.)
#g++ task5.cpp -o task5 -lcrypt
echo crunch 5 5 abc + 123 -t @@@%% -wordlist.txt
crunch 5 5 abc + 123 -t @@@%% -o wordlist.txt #This limitation was implemented for complexity purposes.
echo Do not enter a previously used username. Enter a password \in\ \(\aaa11,aaa12,.. ,bbb21,...,ccc32,ccc33\). Do not enter a previously used password. 
./task5 1
echo Do not enter a previously used username. Enter a password \in \(\aaa11,aaa12,.. ,bbb21,...,ccc32,ccc33\)\. Do not enter a previously used password.
./task5 1
cat passwd
john --wordlist=wordlist.txt passwd


