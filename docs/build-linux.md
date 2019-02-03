# Build on Linux (g++)
### Dependencies
For building sysget on Linux you need no third-party dependecies.<br>
sysget is built with the standard C++ library only<br>
For this you need the following packages:<br>
`g++ make git`<br>
To install it on Debian or Ubuntu simply do:<br>
`sudo apt-get install build-essential`<br>
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
If you are having issues, please open up an issue
