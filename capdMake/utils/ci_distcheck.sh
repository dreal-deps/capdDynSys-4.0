#!/bin/bash

set -e

function start_mxe_env() {
  export PATH=/opt/mxe/usr/bin:$PATH
}



#it is quite difficult to set PATH for jenkins-slave started by launchd on OSX.
export PATH=/usr/local/bin:$PATH
source "$(dirname $0)/ci_configure_flags.sh"
source "$(dirname $0)/ci_funcs.sh"

export CXXFLAGS="-s"
env


if [ -e /opt/mxe ] && [ -n "${HOST_CONFIG}" ]; then #mxe build, cross-platform
  start_mxe_env
  echo "Cross platform build ${HOST_CONFIG}"
else
  echo "default build"
fi

go_to_dist
do_distcheck build_distcheck ""
