#!/bin/bash
make
echo -e 'Test1:'
cat ./Tests/test1.txt
echo -e 'Result:'
./lab2.exe < ./Tests/test1.txt
echo -e '\nTest2:'
cat ./Tests/test2.txt
echo -e 'Result:'
./lab2.exe < ./Tests/test2.txt
echo -e '\nTest3:'
cat ./Tests/test3.txt
echo -e 'Result:'
./lab2.exe < ./Tests/test3.txt
echo -e '\nTest4:'
cat ./Tests/test4.txt
echo -e 'Result:'
./lab2.exe < ./Tests/test4.txt
echo -e '\nTest5:'
cat ./Tests/test5.txt
echo -e '\nResult:'
./lab2.exe < ./Tests/test5.txt
echo -e '\nTest6:'
cat ./Tests/test6.txt
echo -e '\nResult:'
./lab2.exe < ./Tests/test6.txt
echo -e 'Test7:'
cat ./Tests/test7.txt
echo -e 'Result:'
./lab2.exe < ./Tests/test7.txt
echo -e '\nTest8:'
cat ./Tests/test8.txt
echo -e 'Result:'
./lab2.exe < ./Tests/test8.txt
echo -e '\nTest9:'
cat ./Tests/test9.txt
echo -e 'Result:'
./lab2.exe < ./Tests/test9.txt
echo -e '\nTest10:'
cat ./Tests/test10.txt
echo -e 'Result:'
./lab2.exe < ./Tests/test10.txt
echo -e '\nTest11:'
cat ./Tests/test11.txt
echo -e '\nResult:'
./lab2.exe < ./Tests/test11.txt
echo -e '\nTest12:'
cat ./Tests/test12.txt
echo -e '\nResult:'
./lab2.exe < ./Tests/test12.txt
echo -e '\nTest13:'
cat ./Tests/test13.txt
echo -e '\nResult:'
./lab2.exe < ./Tests/test13.txt
make -f Makefile clean

