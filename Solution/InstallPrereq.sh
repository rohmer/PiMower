#!/bin/bash
apt-get update
apt-get install libpoco-dev libi2c-dev -y
apt-get install build-essential git cmake pkg-config -y
apt-get install libjpeg-dev libtiff5-dev libjasper-dev libpng12-dev -y 
apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev -y
apt-get install libxvidcore-dev libx264-dev -y
apt-get install libgtk2.0-dev -y
apt-get install libatlas-base-dev gfortran -y
cd ~
echo "Installing Poco Project"
wget https://pocoproject.org/releases/poco-1.7.9/poco-1.7.9-all.tar.gz
gunzip poco-1.7.9-all.tar.gz
tar -xf poco-1.7.9-all.tar
cd poco-1.7.9-all
./configure --shared --no-tests --omit=NetSSL,Data/SQLite,Data/ODBC
make -j4
make install
cd ~
git clone https://github.com/Itseez/opencv.git
cd opencv
git checkout 3.3.0
cd ~
git clone https://github.com/Itseez/opencv_contrib.git
cd opencv_contrib
git checkout 3.3.0
cd ~/opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=OFF \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
    -D BUILD_DOCS=OFF -D BUILD_PERF_TESTS=OFF -D BUILD_TESTS=OFF \
    -D BUILD_EXAMPLES=OFF ..
make -j1
sudo make install
sudo ldconfig
cd ~
wget https://downloads.sourceforge.net/project/raspicam/raspicam-0.1.6.zip
unzip raspicam-0.1.6.zip
cd raspicam-0.1.6
mkdir build
cd build
cmake ..
make install
cd ~
echo
echo
echo "**** Cleaning Up ****"
echo 
echo 
rm -rf opencv opencv_contrib raspicam*