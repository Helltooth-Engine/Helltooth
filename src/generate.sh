args=vs2019
directory=../Solution
uname=`uname`
if [ $# -gt 0 ]; then
	args=$@
elif [ $uname = "Linux" ]; then
	args=gmake2
fi

if [ -n "`ls -A $directory`" ]; then
	rm -r $directory/
fi

if [ ! -d "$directory" ]; then
	mkdir $directory
fi

if [ ! -d "$directory/Sandbox" ]; then
	mkdir $directory/Sandbox
fi

cp -R demo/res ../Solution/Sandbox/

../bin/premake5 $args --file=premake/premake5.lua
