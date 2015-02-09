#!/bin/bash

set -e

#it is quite difficult to set PATH for jenkins-slave started by launchd on OSX.
export PATH=/usr/local/bin:$PATH
source "$(dirname $0)/ci_configure_flags.sh"
export WITHOUT_CAPD_EXAMPLES=true

env

files=(*.tar.gz)

if [ "1" != "${#files[*]}" ]; then
   echo "ERROR: Found more than one file"
   exit 1
fi

dist_archive=${files[0]}

dist_archive_orig=$(echo ${dist_archive} | sed 's/tar\.gz/orig.tar.gz/' | sed 's/-/_/g')
cp $dist_archive $dist_archive_orig

tar xzf ${dist_archive}

dirs=(*/)

if [ "1" != "${#dirs[*]}" ]; then
   echo "ERROR: Found more than one directory"
   exit 1
fi

dist=${dirs[0]}

cd $dist
cp -fr capdMake/debian ./

export CXXFLAGS="-s"
dpkg-buildpackage -j$(grep -c ^processor /proc/cpuinfo)  -rfakeroot -D -us -uc
