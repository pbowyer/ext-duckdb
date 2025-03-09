FROM debian:bookworm

RUN apt update \
    && apt install -y \
    build-essential \
    autoconf \
    libtool \
    bison \
    re2c \
    pkg-config \
    git \
    libxml2-dev \
    libsqlite3-dev \
    gdb \
    nano \
    procps \
    wget \
    unzip \
    git g++ cmake ninja-build libssl-dev # for duckdb

RUN git clone https://github.com/php/php-src.git --branch=php-8.4.4 --depth=1 \
    && cd php-src \
    && ./buildconf --force \
    && ./configure --enable-debug \
    && make -j $(nproc) \
    && make install \
    && php -v

ENV DUCKDB_SOURCE=/duckdb

RUN mkdir -p ${DUCKDB_SOURCE} \
    && cd ${DUCKDB_SOURCE} \
    && wget https://github.com/duckdb/duckdb/releases/download/v1.2.1/libduckdb-linux-aarch64.zip \
    && unzip libduckdb-linux-aarch64.zip \
    && ls -la \
    && test -f "${DUCKDB_SOURCE}/libduckdb.so" || (echo "DuckDB library not found" && exit 1) \
    && test -f "${DUCKDB_SOURCE}/duckdb.h" || (echo "DuckDB headers not found" && exit 1) 

COPY ./ext /php-src/ext/duckdb
COPY ./tests /php-src/ext/duckdb/tests

WORKDIR /php-src

RUN cd /php-src/ext/duckdb \
    && phpize \
    && ./configure --enable-duckdb --with-duckdb=${DUCKDB_SOURCE} \
    && make \
    && echo "extension=/php-src/ext/duckdb/modules/duckdb.so" >> /usr/local/lib/php.ini

COPY ./launch.json /php-src/.vscode/launch.json