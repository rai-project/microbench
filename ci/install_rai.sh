#! /bin/bash

set -x

set +x
profile="profile:
  firstname: Carl2
  lastname: Pearson2
  username: pearson
  email: pearson@illinois.edu
  access_key: auth0|58e3f85b7234265d51903f8a
  secret_key: ${RAI_SECRET_KEY}
  affiliation: travis
  team:
    name: noteam
  dockerhub:
    username: cwpearson
    password: ${DOCKER_PASSWORD}
"
set -x

set -x

function or_die () {
    "$@"
    local status=$?
    if [[ $status != 0 ]] ; then
        echo ERROR $status command: $@
        exit $status
    fi
}

source ~/.bashrc

if [[ ${DO_BUILD} == 1 ]]; then
    echo "DO_BUILD == 1, not installing rai"
    exit 0
fi

if [[ ${DOCKER_ARCH} != ppc64le ]]; then
    echo "DOCKER_ARCH != ppc64le, not installing rai"
    exit 0
fi

mkdir -p ${RAI_ROOT}
or_die wget -q http://files.rai-project.com/dist/rai/stable/latest/linux-amd64.tar.gz
or_die tar -xvf linux-amd64.tar.gz -C ${RAI_ROOT}
chmod +x ${RAI_ROOT}/rai

set +x
or_die echo "$profile" >> $HOME/.rai_profile
set -x

set +x
exit 0
