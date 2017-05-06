FROM debian:jessie
MAINTAINER Viktor Vorobjov <vostraga@gmail.com>

RUN apt-get update -q \
    && apt-get install -y \
  		libhidapi-hidraw0 \
  		libusb-0.1-4 \
  		libusb-1.0-0 \
  		libhidapi-dev \
      libusb-1.0-0-dev \
  		libusb-dev \
  		libtool \
  		make \
  		automake \
  		pkg-config \
  		gcc-arm-none-eabi \
  		gdb-arm-none-eabi \
      git \
      autoconf \
      texinfo \
    && mkdir /usr/src/; cd /usr/src/ \
    && git clone --depth 1 https://github.com/ntfreak/openocd.git \
    && cd openocd \
    && ./bootstrap \
    && ./configure --enable-stlink --enable-jlink --enable-ftdi --enable-cmsis-dap \
    && make -j"$(nproc)" \
    && make install \
    && cd .. \
    && rm -rf openocd \
    && rm -rf /var/lib/apt/lists/*
    # && apt-get purge -y --auto-remove \
    #   libhidapi-dev \
    #   libusb-1.0-0-dev \
    #   libusb-dev \
    #   libtool \
    #   make \
    #   automake \
    #   pkg-config \
    #   git \
    #   gcc-arm-none-eabi \
    #   gdb-arm-none-eabi \

COPY ./board/st_mapple_f103rb.cfg /usr/local/share/openocd/scripts/board
RUN cp /usr/local/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d/60-openocd.rules
EXPOSE 3333 4444 6666
#ENTRYPOINT ["/usr/local/bin/openocd"]
