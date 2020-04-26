#!/bin/bash
#set -x #echo on

BASEDIR=`pwd`
unamestr=`uname`

case $1 in
    cpm.install)
        wget -O cmake/CPM.cmake https://github.com/TheLartians/CPM.cmake/releases/latest/download/CPM.cmake
        ;;
    sub.init)
        git submodule update --init --recursive
        ;;
    esac
exit 0
