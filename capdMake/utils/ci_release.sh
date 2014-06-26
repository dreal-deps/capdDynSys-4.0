#!/bin/bash


function start_mxe_env() {
  export PATH=/opt/mxe/usr/bin:$PATH
}


function do_config() {
   if [ -n "${HOST_CONFIG}" ]; then
      echo "Cross platform configure ${HOST_CONFIG}"
      ./configure --host=${HOST_CONFIG} --prefix $PWD/install/ --with-boost=${WITH_BOOST}
   else
      echo "Default configure"
      ./configure --prefix $PWD/install/ --with-boost=${WITH_BOOST}
   fi
}

function force_config() {
   rm -fr lib/* bin/*
   do_config || ( autoreconf -fi && do_config )
}

function do_make() {
   JOB="$1"

   echo "do_make ${JOB}"
   make -j ${JOB} || ( force_config && (make -k distclean || true) && force_config && make -j ${JOB} ) || ( rm -fr configure capd.cache && force_config && make -j ${JOB})
}


env

export WITH_BOOST="yes"

if [ -e /opt/mxe ] && [ -n "${HOST_CONFIG}" ]; then #mxe build, cross-platform
  start_mxe_env
  echo "Cross platform build ${HOST_CONFIG}"
  do_make all && do_make install
else
  echo "default build"
  do_make all && do_make install
fi
