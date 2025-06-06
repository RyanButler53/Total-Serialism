FROM alpine:latest AS build


# install lilypond files
RUN apk add lilypond
RUN apk add guile 
RUN apk add font-terminus 
RUN apk add font-urw-base35

# install C++ 
RUN apk update
RUN apk add build-base && apk add cmake>3.31.0

# set working directory
WORKDIR /TotalSerialism

COPY inc/* /TotalSerialism/inc/
COPY src/* /TotalSerialism/src
COPY CMakeLists.txt /TotalSerialism/
COPY score.sh /TotalSerialism/
COPY dockerbuild.sh /TotalSerialism/

# Build in setup of the image.
RUN /TotalSerialism/dockerbuild.sh

CMD [ "ls" ]
