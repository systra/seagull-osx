seagull-osx
===========

### This is the fork of [Seagull](http://gull.sourceforge.net/) (1.8.2), patched for Mac OS X 10.9.4 (Mavericks) and Apple LLVM version 5.1.1 compiler.


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
	
and then start building:

	./build.ksh -target all
	
Optionally you can run:

	./install.ksh
	
to copy Seagull binaries and config files as suggested in `INSTALL.TXT` and perform the remaining actions, if needed.

This has been tested against Seagull 1.8.2 on Mac OS X 10.9.4 (Mavericks) with XCode 5.1.1.
