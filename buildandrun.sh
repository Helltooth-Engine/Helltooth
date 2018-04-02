#!/bin/bash

res_location=res

if [ ! -d $res_location ]; then
	cp -R src/demo/res $res_location
fi

make -d config=debug-gl_x64 -C Solution/
./bin/Sandbox/Sandbox
