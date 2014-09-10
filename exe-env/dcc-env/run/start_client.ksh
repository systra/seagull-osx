#!/bin/ksh

export LD_LIBRARY_PATH=/usr/local/bin
seagull -conf ../config/conf.client.xml -dico ../config/dcc_dictionary_v1_3.xml -scen ../scenario/authorize.client.xml -log ../logs/authorize.client.log -llevel ET

