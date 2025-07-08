FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    git python3 python3-pip gcc-avr avr-libc dfu-programmer dfu-util \
    gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi \
    make unzip wget zip

RUN useradd -ms /bin/bash builder
USER builder
WORKDIR /home/builder

# Install QMK CLI
RUN pip3 install --user qmk

# Setup PATH
ENV PATH="/home/builder/.local/bin:$PATH"

# Clone QMK firmware
RUN qmk setup -y

