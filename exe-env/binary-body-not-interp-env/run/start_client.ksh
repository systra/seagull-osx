#!/bin/ksh

export LD_LIBRARY_PATH=/usr/local/bin

seagull -conf ../config/conf.client.xml -dico ../config/bin-body-not-interp-dico.xml -scen ../scenario/client.xml -log ../logs/client.log -llevel ET

