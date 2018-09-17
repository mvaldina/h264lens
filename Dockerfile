FROM ubuntu:latest
ADD . /root
RUN apt-get update
RUN apt-get -qq -y install meson ninja-build
