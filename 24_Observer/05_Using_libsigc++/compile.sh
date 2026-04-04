#!/bin/sh
# sudo apt install libsigc++-3.0-dev
# pkg-config --cflags --libs sigc++-3.0
# >> -I/usr/include/sigc++-3.0 -I/usr/lib/x86_64-linux-gnu/sigc++-3.0/include -lsigc-3.0
c++ -std=c++23 -O3 -Wall -Wextra -Wpedantic Observer.cpp -o Observer `pkg-config --cflags --libs sigc++-3.0` && Observer
