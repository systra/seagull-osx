#!/bin/ksh

export LD_LIBRARY_PATH=/usr/local/bin

seagull -conf ../config/conf.server.xml -dico ../config/bin-body-not-interp-dico.xml -scen ../scenario/server_2.xml -log ../logs/server_2.log -llevel ET


