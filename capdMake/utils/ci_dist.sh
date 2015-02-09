#!/bin/bash

set -e


# temporary, only for osx. I need a quick build and linux machines are busy
export PATH=/usr/local/bin:$PATH


function do_dist() {
    autoreconf -fi

    BUILD_DIR=build_dist

    if [ -e $BUILD_DIR ]; then
        chmod -R u+rw $BUILD_DIR
        rm -r $BUILD_DIR
    fi

    mkdir -p $BUILD_DIR
    cd $BUILD_DIR
    ../configure --prefix $PWD/install/

    distdir="capd-$(date +%Y%m%d_%H%M)"

    if hash zip 2>/dev/null; then
        make -j dist distdir=$distdir
    else
        echo "Do not have zip"
        make -j dist DIST_TARGETS=dist-gzip distdir=$distdir
    fi


}

#it is quite difficult to set PATH for jenkins-slave started by launchd on OSX.
export PATH=/usr/local/bin:$PATH
source "$(dirname $0)/ci_configure_flags.sh"

env

do_dist
