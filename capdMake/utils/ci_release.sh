#!/bin/bash

set -e

function start_mxe_env() {
  export PATH=/opt/mxe/usr/bin:$PATH
}


function do_config() {
   if [ -n "${HOST_CONFIG}" ]; then
      echo "Cross platform configure ${HOST_CONFIG}"
      ./configure --host=${HOST_CONFIG}
   else
      echo "Default configure"
      ./configure
   fi
}



function do_relese_build() {
    if [ $(uname) == 'Darwin' ]; then
        CORES=$(sysctl hw.ncpu | awk '{print $2}')
    elif [ -e /proc/cpuinfo ]; then
        CORES=$(grep -c ^processor /proc/cpuinfo)
    else
        CORES=""
    fi

    echo "Detected $CORES CPU cores"


    if [ -z "$NODE_NAME" ]; then
        NODE_NAME="jenkins-slave-noname"
    fi
    simple_node_name=$(echo $NODE_NAME  | sed 's/jenkins-slave-\([a-zA-Z0-9_]*\)-[0-9]*$/\1/')
    mkdir build_result

    # it doesn't work with mxe and release build (without autoreconf), why??
    # the problem is in filib and its asm instructions
    #
    # BUILD_DIR=build
    # if [ -e $BUILD_DIR ]; then
    #     chmod -R u+rw $BUILD_DIR
    #     rm -fr $BUILD_DIR
    # fi

    # mkdir -p $BUILD_DIR
    # cd $BUILD_DIR

    do_config

   if [ -n "${HOST_CONFIG}" ]; then
       export host_alias="${HOST_CONFIG}"
   fi

   make -j $CORES

   if [ "$mxe_build" = "yes" ]; then
       BIN_NAME=$(make package_version | grep package_version | sed 's/package_version=\(.*\)/\1/')-dev-winows-mxe
   else
       BIN_NAME=$(make package_version | grep package_version | sed 's/package_version=\(.*\)/\1/')-dev-${simple_node_name}-$(uname -m)
   fi

   make install-strip DESTDIR=$PWD/$BIN_NAME

   if [ "$mxe_build" = "yes" ]; then
       zip -r $BIN_NAME.zip $BIN_NAME
       mv $BIN_NAME.zip build_result/
   else
       tar czf $BIN_NAME.tar.gz $BIN_NAME
       mv $BIN_NAME.tar.gz build_result/
   fi

   mathematica_build=(capdRedHom/programs/apiRedHom-mathematica/capdRedHomM-*.zip)

   if [ -e "${mathematica_build}" ]; then
       mathematica_build_dist=$(basename $(echo "$mathematica_build" | sed "s/\(.*\).zip/\1-${simple_node_name}.zip/"))
       cp $mathematica_build build_result/$mathematica_build_dist
   fi
}

#it is quite difficult to set PATH for jenkins-slave started by launchd on OSX.
export PATH=/usr/local/bin:$PATH
source "$(dirname $0)/ci_configure_flags.sh"

export WITHOUT_CAPD_EXAMPLES=true

env

if [ -e /opt/mxe ] && [ -n "${HOST_CONFIG}" ]; then #mxe build, cross-platform
  start_mxe_env
  mxe_build="yes"
  echo "Cross platform build ${HOST_CONFIG}"
else
  echo "default build"
  mxe_build="no"
fi


files=(*.tar.gz)

if [ "1" != "${#files[*]}" ]; then
   echo "ERROR: Found more than one file"
   exit 1
fi

dist_archive=${files[0]}

tar xzf ${dist_archive}

dirs=(*/)

if [ "1" != "${#dirs[*]}" ]; then
   echo "ERROR: Found more than one directory"
   exit 1
fi

dist=${dirs[0]}

cd $dist
do_relese_build

cd ..
mv $dist/build_result ./
