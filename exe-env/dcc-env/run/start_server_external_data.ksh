#!/bin/ksh

export LD_LIBRARY_PATH=/usr/local/bin
seagull -conf ../config/conf.server_external_data.xml -dico ../config/dcc_dictionary_v1_3.xml -scen ../scenario/authorize.server_external_data.xml -log ../logs/authorize.server_external_data.log -llevel ET 


