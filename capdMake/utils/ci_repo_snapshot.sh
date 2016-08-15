#!/bin/bash

set -e


#it is quite difficult to set PATH for jenkins-slave started by launchd on OSX.
export PATH=/usr/local/bin:$PATH
source "$(dirname $0)/ci_configure_flags.sh"
source "$(dirname $0)/ci_funcs.sh"


output=$PWD/output
cd workdir/src

autoreconf --force --install --verbose
do_dist build "" "$output"

echo $(date +%Y%m%d_%H%M) > $output/build_date
