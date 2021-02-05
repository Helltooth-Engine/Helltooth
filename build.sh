#!/bin/bash
config=debug-gl_x64
res_location=bin/Debug-GL/10000Cubes/res/

clean=`echo $@ | grep -i 'clean'`
count=1
if [ -n "$clean" ]; then
	count=$(($count + 1))
fi

if [ $# -eq $count ]; then
	config=`echo $@ | sed 's/clean\|\ //g'`
fi

if [ -n "$clean" ]; then
	echo "Cleaning..."
	make clean config=$config -C Solution/ > /dev/null
fi
echo "Building..."
make config=$config -C Solution/

echo "Copying resources..."
if [ ! -d $res_location ]; then
	cp -R src/demo/res $res_location
fi



