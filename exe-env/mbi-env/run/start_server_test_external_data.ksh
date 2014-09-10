#!/bin/ksh

#export LD_LIBRARY_PATH=/usr/local/bin
export LD_LIBRARY_PATH=../bin
../bin/seagull -conf ../config/conf.server_external_data.xml -dico ../config/mbi_dictionary_v1_13.xml -scen ../scenario/authorize.server_external_data.xml -log ../logs/authorize.server_external_data.log -llevel E


