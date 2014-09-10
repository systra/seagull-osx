#!/bin/ksh

export LD_LIBRARY_PATH=/usr/local/bin
seagull -conf ../config/conf.client.xml -dico ../config/h225-ras-dictionary.xml -scen ../scenario/client.xml -log ../logs/client.log -llevel ET

