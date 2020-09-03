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


ADD examples /partialcopy/examples
ADD fmt /partialcopy/fmt
ADD memory_buffer /partialcopy/memory_buffer
ADD nonstdstring /partialcopy/nonstdstring
ADD CMakeLists.txt /partialcopy/
ADD usefmt_buf32grow2 /partialcopy/usefmt_buf32grow2
ADD usefmt_buf512grow2 /partialcopy/usefmt_buf512grow2
ADD usefmt_buf1024grow2 /partialcopy/usefmt_buf1024grow2
ADD usefmt_directpushback /partialcopy/usefmt_directpushback
ADD usefmt_erasedbuffer /partialcopy/usefmt_erasedbuffer
ADD usefmt_erasedpushback /partialcopy/usefmt_erasedpushback
ADD usefmt_originalfmt /partialcopy/usefmt_originalfmt
ADD plots /partialcopy/plots
ADD usefmt_singlealloc /partialcopy/usefmt_singlealloc

ADD microbenchmarks /partialcopy/microbenchmarks
ADD benchmark /partialcopy/benchmark

WORKDIR /partialcopy
RUN mkdir build
WORKDIR /partialcopy/build
RUN cmake .. -DCMAKE_CXX_COMPILER=g++-9 -DBUILD_SHARED_LIBS=TRUE -DCMAKE_BUILD_TYPE=RELEASE
RUN make -j6 nonstdstring usefmt_directpushback usefmt_erasedbuffer usefmt_erasedpushback usefmt_singlealloc 
RUN make -j6 fmtsyntax_directpushback fmtsyntax_erasedbuffer fmtsyntax_erasedpushback fmtsyntax_singlealloc
RUN make -j6 printfsyntax_directpushback printfsyntax_erasedbuffer printfsyntax_erasedpushback printfsyntax_singlealloc
ENV LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/fmt/build/ 

RUN echo "change this for complete bloaty output"

RUN bloaty nonstdstring/libnonstdstring.so --domain=vm -d symbols -n 30
RUN bloaty usefmt_directpushback/libusefmt_directpushback.so --domain=vm -d symbols -n 30
RUN bloaty usefmt_erasedbuffer/libusefmt_erasedbuffer.so --domain=vm -d symbols -n 30
RUN bloaty usefmt_erasedpushback/libusefmt_erasedpushback.so --domain=vm -d symbols -n 30
RUN bloaty usefmt_singlealloc/libusefmt_singlealloc.so --domain=vm -d symbols -n 30

RUN ./examples/fmtsyntax_directpushback
RUN bloaty ./examples/fmtsyntax_directpushback --domain=vm -d symbols -n 30 --demangle=full

RUN ./examples/fmtsyntax_erasedbuffer
RUN bloaty ./examples/fmtsyntax_erasedbuffer --domain=vm -d symbols -n 30 --demangle=full

RUN ./examples/fmtsyntax_erasedpushback
RUN bloaty ./examples/fmtsyntax_erasedpushback --domain=vm -d symbols -n 30 --demangle=full

RUN ./examples/fmtsyntax_singlealloc
RUN bloaty ./examples/fmtsyntax_singlealloc --domain=vm -d symbols -n 30 --demangle=full

RUN ./examples/printfsyntax_directpushback
RUN bloaty ./examples/printfsyntax_directpushback --domain=vm -d symbols -n 30 --demangle=full

RUN ./examples/printfsyntax_erasedbuffer
RUN bloaty ./examples/printfsyntax_erasedbuffer --domain=vm -d symbols -n 30 --demangle=full

RUN ./examples/printfsyntax_erasedpushback
RUN bloaty ./examples/printfsyntax_erasedpushback --domain=vm -d symbols -n 30 --demangle=full

RUN ./examples/printfsyntax_singlealloc
RUN bloaty ./examples/printfsyntax_singlealloc --domain=vm -d symbols -n 30 --demangle=full
