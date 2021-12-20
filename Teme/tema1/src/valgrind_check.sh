#!/bin/bash

make	
valgrind --tool=memcheck --leak-check=full --error-exitcode=1 --read-var-info=yes ./WearhouseManager wearhouse parkinglot 2> error

