#!/bin/bash

readonly PROJECT_DIRECTORY="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && cd .. && pwd)"
readonly IMAGE_NAME='arduino-cli-docker:local'

docker run --privileged --rm -t -i -v "${PROJECT_DIRECTORY}:/workspace" \
           -w /workspace "${IMAGE_NAME}" \
           arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega --input-dir build
