#!/bin/bash

set -e

function start_mxe_env() {
  export PATH=/opt/mxe/usr/bin:$PATH
}


function do_config() {
   if [ -n "${HOST_CONFIG}" ]; then
      echo "Cross platform configure ${HOST_CONFIG}"
      ../configure --host=${HOST_CONFIG} --prefix $PWD/install/
   else
      echo "Default configure"
      ../configure --prefix $PWD/install/
   fi
}



function do_distcheck() {
    if [ $(uname) == 'Darwin' ]; then
        CORES=$(sysctl hw.ncpu | awk '{print $2}')
    elif [ -e /proc/cpuinfo ]; then
        CORES=$(grep -c ^processor /proc/cpuinfo)
    else
        CORES=""
    fi

    echo "Detected $CORES CPU cores"

    autoreconf -fi

    BUILD_DIR=build_distcheck

    if [ -e $BUILD_DIR ]; then
        chmod -R u+rw $BUILD_DIR
        rm -r $BUILD_DIR
    fi

    mkdir -p $BUILD_DIR
    cd $BUILD_DIR
    do_config

   if [ -n "${HOST_CONFIG}" ]; then
       export host_alias="${HOST_CONFIG}"
   fi

    if command -v zip 2>/dev/null; then
        make -j $CORES distcheck
    else
        echo "Do not have zip"
        make -j $CORES distcheck DIST_TARGETS=dist-gzip
    fi
}

#it is quite difficult to set PATH for jenkins-slave started by launchd on OSX.
export PATH=/usr/local/bin:$PATH
source "$(dirname $0)/ci_configure_flags.sh"

export CXXFLAGS="-s"
env


if [ -e /opt/mxe ] && [ -n "${HOST_CONFIG}" ]; then #mxe build, cross-platform
  start_mxe_env
  echo "Cross platform build ${HOST_CONFIG}"
else
  echo "default build"
fi

do_distcheck
