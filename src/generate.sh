args=vs2017
directory=../Solution

if [ $# -gt 0 ]; then
	args=$@
fi

if [ ! -d "$directory" ]; then
	mkdir $directory
fi

cp -R demo/res ../Solution/Sandbox/

../bin/premake5 $args --file=premake/premake5.lua