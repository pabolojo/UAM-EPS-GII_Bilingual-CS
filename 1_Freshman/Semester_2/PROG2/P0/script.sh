#!/bin/bash
echo "Compiling e1..."
cd p1_e1
gcc -o p1_e1_executable p1_e1.c node.c
cd ..
echo "Compiling e2..."
cd p1_e2
gcc -o p1_e2_executable p1_e2.c node.c graph.c
cd ..
echo "Compiling e3..."
cd p1_e3
gcc -o p1_e3_executable p1_e3.c node.c graph.c
cd ..
