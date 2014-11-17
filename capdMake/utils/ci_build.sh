#!/bin/bash


export CXXFLAGS="-s"
env



function do_config() {
   rm -fr lib/* bin/*
   ./configure --prefix $PWD/install/ --with-boost=${WITH_BOOST} || ( autoreconf -fi && ./configure --prefix $PWD/install/ --with-boost=${WITH_BOOST} )
}

function do_make() {
   JOB="$1"

   echo "do_make ${JOB}"
   make -j ${JOB} || ( do_config && (make -k distclean || true) && do_config && make -j ${JOB} ) || ( rm -fr configure capd.cache && do_config && make -j ${JOB})
}


do_make all && do_make install
