#!/bin/bash

for f in rsc/*;
do
	gcc $f -o `echo $f | cut -d'.' -f1 | cut -d'/' -f2`
done

cp /bin/ls notc
sed -i '1s/^/NOPE/' notc
