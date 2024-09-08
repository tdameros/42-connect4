FROM alpine:3.19 as builder

RUN apk update && \
    apk add --no-cache \
    make \
    gcc \
    libc-dev \
    && rm -rf /var/cache/apk/*

COPY . /app
WORKDIR /app

RUN make re

FROM alpine:3.19

COPY --from=builder /app/connect4 /usr/local/bin/

WORKDIR /app/

