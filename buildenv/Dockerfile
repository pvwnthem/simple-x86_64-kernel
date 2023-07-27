FROM randomdude/gcc-cross-x86_64-elf

RUN echo "deb http://archive.debian.org/debian stretch main" > /etc/apt/sources.list
RUN apt-get update && apt-get install -y apt-transport-https
RUN apt-get upgrade -y
RUN apt-get install -y nasm
RUN apt-get install -y xorriso
RUN apt-get install -y grub-common
RUN apt-get install -y grub-pc-bin

VOLUME /root/env
WORKDIR /root/env