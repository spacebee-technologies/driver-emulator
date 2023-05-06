FROM ubuntu:22.04

RUN apt-get update
RUN apt-get install -y curl

RUN useradd -u 1000 -m docker-user

# Install arduino-cli
RUN curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
