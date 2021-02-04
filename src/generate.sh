args=vs2019
directory=../Solution
uname=`uname`
premake=../bin/premake5.exe
if [ $# -gt 0 ]; then
	args=$@
elif [ $uname = "Linux" ]; then
	args=gmake2
	premake=../bin/premake5
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

$premake $args --file=premake/premake5.lua
