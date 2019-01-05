#!/bin/sh

BINUTILS_VERSION=2.29
GCC_VERSION=6.3.0
PREFIX="$HOME/opt/cross"
TARGET=i686-elf
PATH="$PREFIX/bin:$PATH"
LANGUAGES=c,c++
MAKE='make -j 4'

brew_path()
{
  brew info $1 | head -n4 | tail -n1 | cut -d' ' -f1
}

build_binutils()
{
  if [[ ! -f "binutils-$BINUTILS_VERSION.tar.gz" ]]
  then
    echo "Downloading binutils-$BINUTILS_VERSION.tar.gz"
    wget ftp://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.gz
  fi

  if [[ ! -d "binutils" ]]
  then 
    mkdir binutils
    tar xfz binutils-$BINUTILS_VERSION.tar.gz -C binutils
    cd binutils
    binutils-$BINUTILS_VERSION/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
    $MAKE
    $MAKE install
    cd ..
  fi
}

build_gcc()
{
  if [[ ! -f "gcc-$GCC_VERSION.tar.gz" ]]
  then
    echo "Downloading gcc-$GCC_VERSION.tar.gz"
    wget ftp://ftp.gnu.org/gnu/gcc/gcc-$GCC_VERSION/gcc-$GCC_VERSION.tar.gz
  fi

  if [[ ! -d "gcc" ]]
  then 
    mkdir gcc
    tar xfz gcc-$GCC_VERSION.tar.gz -C gcc
    brew install gmp mpfr libmpc
    cd gcc
    which -- $TARGET-as || echo $TARGET-as is not in the PATH
    
    gcc-$GCC_VERSION/configure --prefix=$PREFIX \
    --target=$TARGET \
    --disable-nls \
    --enable-languages=$LANGUAGES --without-headers \
    --enable-interwork \
    --enable-multilib \
    --enable-plugin \
    --enable-lto \
    --enable-stage1-checking \
    --with-gmp=$(brew_path gmp) \
    --with-mpfr=$(brew_path mpfr) \
    --with-mpc=$(brew_path libmpc)
    
    $MAKE all-gcc
    $MAKE install-gcc
    $MAKE all-target-libgcc
    $MAKE install-target-libgcc
    cd ..
  fi
}

build_binutils
build_gcc
