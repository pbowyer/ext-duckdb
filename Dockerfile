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
    procps

RUN git clone https://github.com/php/php-src.git --branch=php-7.4.33 --depth=1 \
    && cd php-src \
    && ./buildconf --force \
    && ./configure --enable-debug \
    && make -j $(nproc) \
    && make install \
    && php -v

COPY ./ext /php-src/ext/hello

WORKDIR /php-src

RUN cd /php-src/ext/hello \
    && phpize \
    && ./configure --enable-hello \
    && make \
    && echo "extension=/php-src/ext/hello/modules/hello.so" >> /usr/local/lib/php.ini

COPY ./launch.json /php-src/.vscode/launch.json