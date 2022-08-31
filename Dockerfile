FROM ubuntu:22.04

RUN apt update
RUN apt install make=4.3-4.1build1 g++=4:11.2.0-1ubuntu1 -y

WORKDIR /app
COPY app .

RUN make
RUN /app/dist/programa
