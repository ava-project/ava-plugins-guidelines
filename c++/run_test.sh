#!/bin/sh

mkdir build; cd build ; cmake ../ ; make ; clear ; ./test_server ; cd .. ; rm -rf build ; clear ; ls
