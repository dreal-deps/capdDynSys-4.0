#!/bin/bash


function go_to_dist() {
    files=(capd-*.tar.gz)

    if [ "1" != "${#files[*]}" ]; then
        echo "ERROR: Found more than one file"
        exit 1
    fi

    dist_archive=${files[0]}

    tar xzf ${dist_archive}

    dirs=(capd-*/)

    if [ "1" != "${#dirs[*]}" ]; then
        echo "ERROR: Found more than one directory"
        exit 1
    fi

    dist=${dirs[0]}
    cd $dist
}

function pwd_version() {
    echo $(basename $PWD) | sed 's/capd.*-\(.*\)/\1/'
}

function detect_cores() {
    if [ -z "$CORES" ]; then
        if [ $(uname) == 'Darwin' ]; then
            CORES=$(sysctl hw.ncpu | awk '{print $2}')
        elif [ -e /proc/cpuinfo ]; then
            CORES=$(grep -c ^processor /proc/cpuinfo)
        else
            CORES="1"
        fi
        echo "Using $CORES CPU cores"
    else
        echo "CORES set to $CORES"
    fi
}

function do_distcheck() {
    BUILD_DIR="$1"
    MAKE_ARGS="$2"

    detect_cores

#    autoreconf --force --install --verbose


    if [ -e $BUILD_DIR ]; then
        chmod -R u+rw $BUILD_DIR
        rm -r $BUILD_DIR
    fi

    mkdir -p $BUILD_DIR
    cd $BUILD_DIR

   if [ -n "${HOST_CONFIG}" ]; then
      echo "Cross platform configure ${HOST_CONFIG}"
      ../configure --host=${HOST_CONFIG} --prefix $PWD/install/
   else
      echo "Default configure"
      ../configure --prefix $PWD/install/
   fi


   if [ -n "${HOST_CONFIG}" ]; then
       export host_alias="${HOST_CONFIG}"
   fi

    if command -v zip 2>/dev/null; then
        make -j $CORES distcheck $MAKE_ARGS
# default do not create zip. Do it leter, so distcheck do not compleain about not cleaned files
        make -j $CORES dist DIST_TARGETS="dist-zip" $MAKE_ARGS
    else
        echo "Do not have zip"
        make -j $CORES distcheck $MAKE_ARGS
    fi
}


function do_dist() {
    BUILD_DIR="$1"
    MAKE_ARGS="$2"


    if [ -e $BUILD_DIR ]; then
        chmod -R u+rw $BUILD_DIR
        rm -r $BUILD_DIR
    fi

    mkdir -p $BUILD_DIR
    cd $BUILD_DIR

    ../configure

    if command -v zip 2>/dev/null; then
        make -j $CORES dist DIST_TARGETS="dist-gzip dist-zip" $MAKE_ARGS
    else
        echo "Do not have zip"
        make -j $CORES dist DIST_TARGETS=dist-gzip $MAKE_ARGS
    fi
}
