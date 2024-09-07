FROM alpine:3.19 as builder

RUN apk update && \
    apk add --no-cache \
    make \
    gcc \
    ncurses-dev \
    libc-dev \
    && rm -rf /var/cache/apk/*

COPY . /app
WORKDIR /app

RUN make re

FROM alpine:3.19

RUN apk update && \
    apk add --no-cache \
    ncurses-libs \
    && rm -rf /var/cache/apk/*

COPY --from=builder /app/connect4 /usr/local/bin/

ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8
ENV TERM xterm-256color

WORKDIR /app/

