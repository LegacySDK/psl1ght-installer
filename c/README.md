# psl1ght-installer
The C version (aka the coolest >:3)
## Dependencies
psl1ght-installer depends on `curl`, `unzip`, `git`, `make` and `cmake`.\
Install them somehow.

## Building
Please build CURL first!
```sh
cd ./third-party/curl-8.21.0/
mkdir build && cd build
cmake ..
make -j$(nproc)
```
## TODO
make it work on windows
