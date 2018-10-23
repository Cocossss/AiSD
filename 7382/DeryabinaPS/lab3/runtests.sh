#!/bin/bash

gcc ./Source/lab3.c -o lab3.exe

echo -e '\n\n\033[7mTest1:\033[0m'
cat ./Tests/test1.txt
echo -e 'Result:'
./lab3.exe < ./Tests/test1.txt

echo -e '\n\n\033[7mTest2:\033[0m'
cat ./Tests/test2.txt
echo -e 'Result:'
./lab3.exe < ./Tests/test2.txt

echo -e '\n\n\033[7mTest3:\033[0m'
cat ./Tests/test3.txt
echo -e 'Result:'
./lab3.exe < ./Tests/test3.txt

echo -e '\n\n\033[7mTest4:\033[0m'
cat ./Tests/test4.txt
echo -e 'Result:'
./lab3.exe < ./Tests/test4.txt

echo -e '\n\n\033[7mTest5:\033[0m'
cat ./Tests/test5.txt
echo -e 'Result:'
./lab3.exe < ./Tests/test5.txt

echo -e '\n\n\033[7mTest6:\033[0m'
cat ./Tests/test6.txt
echo -e 'Result:'
./lab3.exe < ./Tests/test6.txt

echo -e '\n\n\033[7mTest7:\033[0m'
cat ./Tests/test7.txt
echo -e 'Result:'
./lab3.exe < ./Tests/test7.txt

echo -e '\n\n\033[7mTest8:\033[0m'
cat ./Tests/test8.txt
echo -e 'Result:'
./lab3.exe < ./Tests/test8.txt

echo -e '\n\n\033[7mTest9:\033[0m'
cat ./Tests/test9.txt
echo -e 'Result:'
./lab3.exe < ./Tests/test9.txt

echo -e '\n\n\033[7mTest10:\033[0m'
cat ./Tests/test10.txt
echo -e 'Result:'
./lab3.exe < ./Tests/test10.txt

echo -e '\n\n\033[7mTest11:\033[0m'
cat ./Tests/test11.txt
echo -e 'Result:'
./lab3.exe < ./Tests/test11.txt
