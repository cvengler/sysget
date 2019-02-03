# Build on macOS/Darwin (clang)
### Dependencies
For building sysget on macOS you need no third-party dependecies.<br>
sysget is built with the standard C++ library only<br>
For this you simply need a C++ compiler which is included in Xcode.<br>
Please download Xcode from the Mac App Store<br>
### Before the build
Simply clone the git repository.<br>
If you want to build a specifc release do:<br>
`git tag` and then do `git checkout vX.X` where X.X is your version.<br>
### Build
```
make
sudo make install
```
That's it. Compiling takes around 2-5 seconds.<br>
If you have issues, please open up an issue
