FROM local/openocd
MAINTAINER Viktor Vorobjov <vostraga@gmail.com>

RUN apt-get update -q \
    && apt-get install -y \
    software-properties-common \
    ccache \
    python \
    curl \
    wget \
    bzip2 \
    mc \
    python-pip \
    python-setuptools \
    mercurial \
    && rm -rf /var/lib/apt/lists/*


RUN cd /usr/src/ \
 && git clone --depth 1 https://github.com/ARMmbed/mbed-cli \
 && cd mbed-cli \
 && python setup.py install

#ENTRYPOINT ["/usr/local/bin/openocd"]
#EXPOSE 3333 4444 6666
