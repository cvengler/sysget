#!/bin/bash
echo "Enter a version number"
read version

echo "Enter architecture"
read arch

echo "Enter your name"
read name

echo "Enter your email"
read email

# Create needed dirs
mkdir -p sysget-$version-$arch
mkdir -p sysget-$version-$arch/DEBIAN
mkdir -p sysget-$version-$arch/usr/local
mkdir -p sysget-$version-$arch/usr/local/bin
mkdir -p sysget-$version-$arch/etc
mkdir -p sysget-$version-$arch/etc/bash_completion.d/

# Package control file
echo "Package: sysget
Version: $version
Architecture: $arch
Maintainer: $name <$email>
Description: One package manager to rule them all
Homepage: http://sysget.emilengler.com
Priority: standard
" > sysget-$version-$arch/DEBIAN/control

# sysget config file to allow purging
echo "apt-get" > sysget-$version-$arch/etc/sysget

# Compile
make -C ../
cp ../sysget.o sysget-$version-$arch/usr/local/bin/sysget
make -C ../ clean
# Copy the autocompletion
cp bash-completion.bash sysget-$version-$arch/etc/bash_completion.d/sysget
# Build the deb
dpkg-deb -b sysget-$version-$arch
# Remove the folder
rm -rf sysget-$version-$arch/
echo "Done file saved to sysget-$version-$arch.deb"