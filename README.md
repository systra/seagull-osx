seagull-osx
===========

### This is the fork of [Seagull](http://gull.sourceforge.net/) (1.8.2), patched for Mac OS X 10.9.4 (Mavericks) and Apple LLVM version 5.1.1 compiler (also working on OS X 10.10 Yosemite).

## Building

Seagull is a free and Open Source (GPL) multi-protocol 
traffic generator test tool. 
Primary aimed at IMS protocols (and thus being the perfect 
complement to [SIPp](http://sipp.sourceforge.net) for IMS testing), 
Seagull is a powerful traffic generator for functional, load, 
endurance, stress and performance tests for almost any kind of protocol.

More information: [http://gull.sourceforge.net/](http://gull.sourceforge.net/)

Make sure to set environment variables before compilation:

	export LC_CTYPE=C 
	export LANG=C

**For XCode 7.x use command below before buliding step!**

	export CFLAGS="-DHAVE_HTONLL"
	
and then start building:

	./build.ksh -target all
	
After successfull building you can use binaries from *bin *directory or optionally run install script:

	./install.ksh
	
to copy Seagull binaries and config files as suggested in `INSTALL.TXT` and perform the remaining actions, if needed.

## Using binary package

Binary is ready for use *OS X* (tested on Mavericks and Yosemite).

1. Extract binary package (for example to: `/opt/seagull` directory`)
2. Set environment paths

  - Add Seagull's libraries to `LD_LIBRARY_PATH`:
  
	`export LD_LIBRARY_PATH=/opt/seagull/bin`

  - You can also add Seagull executable to `PATH`:

	`export PATH=/opt/seagull/bin:$PATH`

You can start using seagull now!

