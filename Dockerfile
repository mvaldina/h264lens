FROM ubuntu:latest

RUN apt-get update
RUN apt-get -qq -y install meson ninja-build build-essential
RUN  DEBIAN_FRONTEND=noninteractive apt-get -qq -y install libgtk-3-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev
RUN  DEBIAN_FRONTEND=noninteractive apt-get -qq -y install libgstreamer-plugins-good1.0-dev

ADD . /root