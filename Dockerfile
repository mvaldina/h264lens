FROM ubuntu:latest
ADD . /root

CMD apt-get install meson ninja