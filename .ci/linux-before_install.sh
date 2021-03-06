#!/usr/bin/env bash

# Installs the dependencies need for travis ci linux
sudo apt-get update --fix-missing
sudo apt-get update -qq
sudo apt-get install -y \
    libfreetype6-dev \
    libx11-dev \
    libstdc++6 \
    libc++-dev \
    libxinerama-dev \
    libxrandr-dev \
    libxcursor-dev \
    libxcomposite-dev \
    mesa-common-dev \
    libasound2-dev \
    freeglut3-dev \
    libcurl4-gnutls-dev+ \
    libasound2-dev \
    libsndfile1 \
    libjack-dev
sudo add-apt-repository -y ppa:webkit-team/ppa
sudo apt-get update
sudo apt-get install libwebkit2gtk-4.0-37 libwebkit2gtk-4.0-dev
sudo apt-get update --fix-missing