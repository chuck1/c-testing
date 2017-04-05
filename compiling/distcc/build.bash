#!/bin/bash
export DISTCC_HOSTS=`cat ~/hostsfile`
#make -j6

distcc gcc main.c

