#!/bin/bash

files="html/index.html makefile Voting.c++ Voting.h Voting.log \
RunVoting.c++ RunVoting.in RunVoting.out UVaVoting.c++ \
TestVoting.c++ TestVoting.out"

tempdir=verifytemp

if [ ! -e "Voting.zip" ]
then
  echo "Error: Couldn't find Voting.zip"
else
  echo "Found Voting.zip."
  [ -d $tempdir ] || mkdir $tempdir
  cd $tempdir
  echo "Extracting the archive..."
  unzip -n ../Voting.zip
  echo "Done."
  for f in $files
  do
    echo -n "Checking for $f... "
    if [ ! -e "$f" ]
    then
      echo "ERROR: file missing from the current folder."
    else
      echo "Present."
    fi
  done
  cd ..
fi
