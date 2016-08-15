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
    ppwd=$(pwd)
    output="$1"

    ver="$(pwd_version)"

    mkdir -p "$output"

    if [ $(uname) == 'Darwin' ]; then
        CORES=$(sysctl hw.ncpu | awk '{print $2}')
    elif [ -e /proc/cpuinfo ]; then
        CORES=$(grep -c ^processor /proc/cpuinfo)
    else
        CORES=""
    fi

    echo "Detected $CORES CPU cores"

    if [ -z "${TARGET_HOST}" ]; then
        echo "Please set TARGET_HOST, e.g. ubuntu_14.04" >& 2
        exit 1
    fi

    echo "TARGET_HOST=${TARGET_HOST}"

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

   make -j $CORES check

   if [ "$mxe_build" = "yes" ]; then
       #       BIN_NAME=$(make package_version | grep package_version | sed 's/package_version=\(.*\)/\1/')-dev-winows-mxe
              BIN_NAME="capd-${ver}-dev-winows-mxe"
   else
       #       BIN_NAME=$(make package_version | grep package_version | sed 's/package_version=\(.*\)/\1/')-dev-${TARGET_HOST}-$(uname -m)
              BIN_NAME="capd-${ver}-dev-${TARGET_HOST}-$(uname -m)"
   fi

   make install-strip DESTDIR=$PWD/$BIN_NAME

   find $BIN_NAME -type f -print > files.lst

   if [ "$mxe_build" = "yes" ]; then
       zip -r $BIN_NAME.zip $BIN_NAME
       mv $BIN_NAME.zip $output/
   else
       tar zcvf $BIN_NAME.tar.gz $(cat files.lst)
       mv $BIN_NAME.tar.gz $output/
   fi

   cd $ppwd
}

#it is quite difficult to set PATH for jenkins-slave started by launchd on OSX.
export PATH=/usr/local/bin:$PATH
source "$(dirname $0)/ci_configure_flags.sh"
source "$(dirname $0)/ci_funcs.sh"
source "$(dirname $0)/ci_target_host.sh"

export WITHOUT_CAPD_EXAMPLES=true


output=$PWD/output
input=$PWD/input

env

if [ -e /opt/mxe ] && [ -n "${HOST_CONFIG}" ]; then #mxe build, cross-platform
  start_mxe_env
  mxe_build="yes"
  echo "Cross platform build ${HOST_CONFIG}"
else
  echo "default build"
  mxe_build="no"
fi

go_to_dist
do_relese_build "$output"
mv $input/build_date $output/
