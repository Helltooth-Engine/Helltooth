args=vs2017
if [ $# -gt 0 ]; then
	args=$@
fi

mkdir ../Solution

cp -R demo/res ../Solution/Sandbox/

../bin/premake5 $args --file=premake/premake5.lua
