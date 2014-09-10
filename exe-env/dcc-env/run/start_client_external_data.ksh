#!/bin/ksh

export LD_LIBRARY_PATH=/usr/local/bin
seagull -conf ../config/conf.client_external_data.xml -dico ../config/dcc_dictionary_v1_3.xml -scen ../scenario/authorize.client_external_data.xml -log ../logs/authorize.client_external_data.log -llevel E

