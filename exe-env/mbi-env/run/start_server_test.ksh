#!/bin/ksh

#export LD_LIBRARY_PATH=/usr/local/bin
export LD_LIBRARY_PATH=../bin
export SH_LIB_PATH=../bin
../bin/seagull -conf ../config/conf.server.xml -dico ../config/mbi_dictionary_v1_13.xml -scen ../scenario/authorize.server.xml -log ../logs/authorize.server.log -llevel A


