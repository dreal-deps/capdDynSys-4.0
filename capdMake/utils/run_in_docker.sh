#!/bin/bash
set -e

docker_image="$1"
cmd="$2"

export docker_image
source "$(dirname $0)/ci_target_host.sh"

cid_file=$(mktemp)
rm ${cid_file}


docker -H unix:///run/docker.sock pull docker.capdnet:5000/"${docker_image}" # refresh

docker -H unix:///run/docker.sock run --rm --cidfile="${cid_file}" --user="$(id -u)" --workdir="$PWD" --volumes-from="$(hostname -s)" -e "TARGET_HOST=${TARGET_HOST}"  docker.capdnet:5000/"${docker_image}" /bin/bash -c "${cmd}"

#cid=$(cat "${cid_file}")
#docker stop "${cid}"
#docker rm "${cid}"
