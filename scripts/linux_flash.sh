#!/bin/bash

readonly PROJECT_DIRECTORY="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && cd .. && pwd)"
readonly IMAGE_NAME='ghcr.io/spacebee-technologies/arduino-environment:v0.1.0'

docker run --privileged --rm -t -i -v "${PROJECT_DIRECTORY}:/workspace" \
           -w /workspace -v /dev:/dev "${IMAGE_NAME}" \
           bash -c 'arduino-cli core install arduino:avr;
                    arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega -t -v --input-dir build'
