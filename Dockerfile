ARG REG_HOST

FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive
WORKDIR /root

RUN apt-get update --quiet && apt-get install --yes \
				clang-14 	    \
				cmake		    \
				curl		    \
				expect		    \
				git		    \
				graphviz	    \
				python3		    \
				ninja-build         \
				python3		    \
				python3-pip         \
				wget                \
				ssh		    \
				software-properties-common \
				wget		    \
				&& apt-get autoremove --quiet --yes \
				&& rm -rf /var/lib/apt/lists/*

RUN curl -OL https://go.dev/dl/go1.20.linux-amd64.tar.gz \
	&& tar -C /usr/local -xf go1.20.linux-amd64.tar.gz

RUN mkdir /go && mkdir /go/bin
ENV GOBIN=/go/bin
ENV PATH=$PATH:/usr/local/go/bin
ENV PATH=$PATH:$GOBIN:$GOPATH/bin

RUN go install github.com/cucumber/godog/cmd/godog@latest

RUN update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-14 1
RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-14 1

RUN pip3 install conan

RUN git clone --depth 1 https://github.com/llvm/llvm-project.git /home/llvm

RUN mkdir -p /home/llvm/build
WORKDIR "/home/llvm/build"

RUN CXX=clang++ CC=clang cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" ../llvm

RUN ninja install
RUN ninja check-clang

RUN apt-get --purge autoremove clang-14 --yes

RUN ninja -t clean

