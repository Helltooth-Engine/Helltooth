# Helltoth
## What is Helltooth?
Helltooth is wanna-be game engine written from almost scratch.
Helltooth currently supports two graphics APIs:
* DirectX
* OpenGL (the PC version)

As well as two platforms:
* Windows
* Linux -- linux is currently in a buggy state so it might build but may not run

## Building Helltooth
Helltooth is constructed using [Premake](https://github.com/premake/premake-core).
#### Building Helltooth on Linux:
To build Helltooth on Linux you first have to install all the dependencies and libs that are required:
```
sudo apt-get install gcc-multilib g++-multilib mesa-common-dev
```
(and a few others which I'll link soon)
**NOTE:** If you can't run the shell scripts you have two options:
1) Make the script and executable using chmod: `sudo chmod +x <scriptname>`
2) Run it via bash `sudo bash <scriptname>`

After installing all the dependencies required you're going to have to create the make scripts to do that you first initialize premake
```
sudo ./init.sh
```
Now you can generate the make files, go into `src/` and write 
```
sudo ./generate.sh gmake
```
The make files should appear in the root directory in `Solution/`, once you got them you can now build by doing 
```
make config=<configuration> -C Solution/
``` 
where <configuration> can be: `debug-gl_x86` or `debug-gl_x64`
To run the application you just type 
```
./bin/Sandbox/Sandbox
```
**NOTE:** Because I had to build and run numerous times on linux there's also a build and run script which you can just run by doing: `./buildandrun.sh`

#### Building Helltooth on Windows:
Building Helltooth on Windows is definitely easier.
First of all you're going to need some sort of bash console to run the bash scripts, but if you use Git Bash you should already have that installed
Once you got a bash terminal installed you can proceed to building Helltooth.
First step is to run the init script
```
./init.sh
```

Now we need to generate the project for your preferred IDE (make sure premake supports it), first go into `src/`
If you want to build for Visual Studio 2017
```
./generate.sh vs2017
```

After that you can just go into `Solution/` and open the project and build and run it