#!/bin/bash
while true; do
	./maker > test.txt
   	./a < test.txt > ans.txt
	./b < test.txt > out.txt
	diff ans.txt out.txt 
	if [ $? -ne 0 ] ; then break; fi
done
