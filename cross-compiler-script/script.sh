#!/bin/bash
set -e # Exit immediately if a command exits with a non-zero status.

# --- Configuration ---
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

# --- Dependencies ---
sudo dnf install -y bison flex gmp-devel mpfr-devel libmpc-devel texinfo

# --- Build Steps ---
mkdir -p "$HOME/src"
cd "$HOME/src"

# 1. Build Binutils
wget -c https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz
tar -xf binutils-2.42.tar.xz
mkdir -p build-binutils
cd build-binutils
../binutils-2.42/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..

# 2. Build GCC
wget -c https://ftp.gnu.org/gnu/gcc/gcc-14.1.0/gcc-14.1.0.tar.xz
tar -xf gcc-14.1.0.tar.xz
mkdir -p build-gcc
cd build-gcc
../gcc-14.1.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
cd ..

echo "------------------------------------------------"
echo "Cross-compiler built and installed in $PREFIX"
echo "Add the following line to your ~/.bashrc or ~/.zshrc:"
echo "export PATH=\"$HOME/opt/cross/bin:\$PATH\""
echo "------------------------------------------------"

