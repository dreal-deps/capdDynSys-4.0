#!/bin/bash
set -e

image="$1"
cmd="$2"


cid_file=$(mktemp)
rm ${cid_file}

docker run --rm --cidfile="${cid_file}" --user="$(id -u)" --workdir="$PWD" --volumes-from="$(hostname -s)" docker.capdnet:5000/"${image}" /bin/bash -c "${cmd}"

#cid=$(cat "${cid_file}")
#docker stop "${cid}"
#docker rm "${cid}"
