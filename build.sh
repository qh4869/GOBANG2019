#!/bin/bash

SCRIPT=$(readlink -f "$0")
BASEDIR=$(dirname "$SCRIPT")
cd $BASEDIR

BIN=bin
BUILD=build

if [ $? -ne 0 ] 
then
    exit -1
fi

if [ ! -d src ] || [ ! -f readme.md ]
then
    echo "ERROR: $BASEDIR is not a valid directory of SDK-gcc for GOBANG."
    echo "  Please run this script in a regular directory of SDK-gcc."
    exit -1
fi
cmake --version 2>&1
tmp=$?
if [ ${tmp} -ne 0 ]
then
    echo "ERROR: You should install cmake(2.8 or later) first."
    exit
fi

rm -fr ${BIN}
mkdir $BIN
rm -fr $BUILD
mkdir $BUILD
cd $BUILD

cmake ../src
tmp=$?
echo "cmake return:" ${tmp}
if [ ${tmp} -ne 0 ]
then
 echo "cmake <>return:" ${tmp}
 exit -1
fi

make
tmp=$?
 echo "make return:" ${tmp}
if [ ${tmp} -ne 0 ]
then
echo "make <>return:" ${tmp}
 exit -1
fi

echo =====running=======
../bin/GOBANG