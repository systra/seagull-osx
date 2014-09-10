#!/bin/ksh

export LD_LIBRARY_PATH=/usr/local/bin
seagull -conf ../config/conf.client.xml -dico ../config/mbi_dictionary_v1_13.xml -scen ../scenario/authorize.client.xml -log ../logs/authorize.client.log -llevel ET

