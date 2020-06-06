# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest

WORKDIR /
RUN touch /preseed.txt
RUN echo "tzdata tzdata/Areas select Europe" >> preseed.txt
RUN echo "tzdata tzdata/Zones/Europe select Zurich" >> preseed.txt

## for apt to be noninteractive
ARG DEBIAN_FRONTEND=noninteractive
ARG DEBCONF_NONINTERACTIVE_SEEN=true

RUN debconf-set-selections /preseed.txt

# Update apps on the base image
RUN apt-get -y update && apt-get install -y
RUN apt-get install -y cmake protobuf-compiler git g++-9 pkg-config

RUN git clone https://github.com/google/bloaty.git
WORKDIR /bloaty
RUN mkdir build
WORKDIR /bloaty/build
RUN cmake .. -DCMAKE_CXX_COMPILER=g++-9
RUN make -j6
RUN make install

RUN echo "change this for complete output"

ADD fmt /nonstdstring/fmt
ADD CMakeLists.txt /nonstdstring/
ADD *.cpp /nonstdstring/
ADD include /nonstdstring/include

WORKDIR /nonstdstring
RUN mkdir build
WORKDIR /nonstdstring/build
RUN cmake .. -DCMAKE_CXX_COMPILER=g++-9 -DBUILD_SHARED_LIBS=TRUE -DCMAKE_BUILD_TYPE=RELEASE
RUN make -j6
ENV LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/fmt/build/ 

RUN bloaty libnonstdstring.so --domain=vm -d symbols -n 30

RUN ./usefmt
RUN bloaty usefmt --domain=vm -d symbols -n 100 --demangle=full

RUN ./useprintf
RUN bloaty useprintf --domain=vm -d symbols -n 100 --demangle=full
