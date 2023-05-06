#!/bin/bash

readonly PROJECT_DIRECTORY="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && cd .. && pwd)"

cd "${PROJECT_DIRECTORY}/docker"
docker build -t arduino-cli-docker:local .
