#   \file
#   \brief Dockerfile for creating a development container for Gaisler LEON devices software
#   \author Denis Tcherniak
#   \date 13/06/2024
#   \copyright Copyright © [2024] Technical University of Denmark 
#   \copyright This code is licensed under BSD 3-Clause License (see LICENSE.txt for details)

# We base the container on a standard ubuntu installation
FROM ubuntu:latest

# Specify which versions of BCC and MKPROM2 to get and install
ENV BCC_VERSION=2.3.1
# This line must be uncommented for BCC versions >= 2.3.0, as Gaisler decided to rename the toolchain
ENV BCC_PREFIX=sparc-
ENV MKPROM2_VERSION=2.0.69

# Make the prompt non-interactive to avoid interactive inputs stalling the installation
ENV DEBIAN_FRONTEND=noninteractive

# Update the system and install dependencies
RUN apt update && apt upgrade -y && apt install -y wget xz-utils make git gpgconf openssh-server openssh-client sudo

# Install gcc, build tools and gdb
RUN apt install -y build-essential gcc gdb

# Required to support older BCC versions, only tested with 2.2.2
RUN wget http://security.ubuntu.com/ubuntu/pool/universe/n/ncurses/libtinfo5_6.3-2ubuntu0.1_amd64.deb
RUN wget http://security.ubuntu.com/ubuntu/pool/universe/n/ncurses/libncursesw5_6.3-2ubuntu0.1_amd64.deb
RUN dpkg -i libtinfo5_6.3-2ubuntu0.1_amd64.deb
RUN dpkg -i libncursesw5_6.3-2ubuntu0.1_amd64.deb

# Download BCC & MKPROM2
RUN wget 'https://download.gaisler.com/anonftp/bcc2/bin/bcc-'$BCC_VERSION'-gcc-'$BCC_PREFIX'linux64.tar.xz' 
RUN wget 'https://download.gaisler.com/anonftp/mkprom2/mkprom2-'$MKPROM2_VERSION'.tar.gz'

# Extract BCC and put it into path
RUN tar -xJf 'bcc-'$BCC_VERSION'-gcc-'$BCC_PREFIX'linux64.tar.xz' -C /opt/.
ENV PATH='/opt/'$BCC_PREFIX'bcc-'$BCC_VERSION'-gcc/bin:'$PATH

# Extract MKPROM2 and put it into path
RUN tar -xzf mkprom2-$MKPROM2_VERSION'.tar.gz' -C /opt/.
ENV PATH="/opt/mkprom2:$PATH"

# Argument defaults (these will be overridden by build args)
ARG USER_NAME=vscode
ARG USER_UID=1000
ARG USER_GID=1000

# Create a non-root user with the specified UID and GID
RUN groupadd --gid $USER_GID $USER_NAME
RUN useradd --uid $USER_UID --gid $USER_GID -m $USER_NAME
RUN echo "$USER_NAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
RUN usermod --shell /bin/bash $USER_NAME

# Set the user
USER $USER_NAME

# Set the working directory
WORKDIR /workspaces
