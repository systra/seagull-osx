#!/bin/ksh

export LD_LIBRARY_PATH=/usr/local/bin

seagull -conf ../config/conf.server.xml -dico ../config/bin-body-not-interp-dico.xml -scen ../scenario/server.xml -log ../logs/server.log -llevel ET


