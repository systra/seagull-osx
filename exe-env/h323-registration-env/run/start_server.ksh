#!/bin/ksh

export LD_LIBRARY_PATH=/usr/local/bin
seagull -conf ../config/conf.server.xml -dico ../config/h225-ras-dictionary.xml -scen ../scenario/server.xml -log ../logs/server.log -llevel ET 


