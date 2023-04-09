# 1、openssl：

```bash
https://github.com/openssl/openssl/releases
wget https://github.com/openssl/openssl/releases/download/openssl-3.1.0/openssl-3.1.0.tar.gz

tar -xvf openssl-3.1.0.tar.gz
cd openssl-3.1.0
mkdir -p build-aarch64/install
cd build-aarch64
../Configure linux-aarch64 --cross-compile-prefix=aarch64-linux-gnu- --prefix=$PWD/install shared
make -j
make install
```

# 2、zlib：

```bash
http://www.zlib.net/
wget http://www.zlib.net/zlib-1.2.13.tar.gz

tar -xvf zlib-1.2.13.tar.gz
cd zlib-1.2.13
cd build-aarch64
export CROSS_COMPILE=aarch64-linux-gnu-
export CC=aarch64-linux-gnu-gcc
export AR=aarch64-linux-gnu-ar
export RANLIB=aarch64-linux-gnu-gcc-ranlib
CFLAGS="-fPIC" ../configure --static --prefix=$PWD/install
make
make install
```

# 3、openssh：

```bash
https://www.openssh.com/portable.html
wget https://mirrors.aliyun.com/pub/OpenBSD/OpenSSH/portable/openssh-9.3p1.tar.gz

tar -xvf openssh-9.3p1.tar.gz
cd openssh-9.3p1
mkdir -p build-aarch64/install
cd build-aarch64
../configure --host=aarch64-linux-gnu --with-zlib=/home/hx/code/others/zlib-1.2.13/build-aarch64/install --with-ssl-dir=/home/hx/code/others/openssl-3.1.0/build-aarch64/install --prefix=$PWD/install --disable-etc-default-login
make -j
make install
```

