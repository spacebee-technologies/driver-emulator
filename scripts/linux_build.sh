#!/bin/bash

readonly PROJECT_DIRECTORY="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && cd .. && pwd)"
readonly IMAGE_NAME='ghcr.io/spacebee-technologies/arduino-environment:v0.1.0'

docker run --privileged --rm -t -i -v "${PROJECT_DIRECTORY}:/workspace" \
           -w /workspace "${IMAGE_NAME}" \
           bash -c 'arduino-cli lib install autowp-mcp2515;
                    arduino-cli core install arduino:avr;
                    arduino-cli compile --fqbn arduino:avr:mega --output-dir build Arduino_CanOpen/'
