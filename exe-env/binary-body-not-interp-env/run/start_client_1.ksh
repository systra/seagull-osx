#!/bin/ksh

export LD_LIBRARY_PATH=/usr/local/bin

seagull -conf ../config/conf.client.xml -dico ../config/bin-body-not-interp-dico.xml -scen ../scenario/client_1.xml -log ../logs/client_1.log -llevel ET

