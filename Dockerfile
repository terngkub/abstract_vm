FROM ubuntu:18.04

# install g++
RUN apt update
RUN apt install -y g++
RUN apt install -y make

# copy and build
WORKDIR /usr/src/abstract_vm
COPY . .
RUN make -j 4

# run the program
CMD ["./avm"]
