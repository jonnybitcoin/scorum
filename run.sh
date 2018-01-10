#!/bin/bash

echo "==================================="
echo echo $SHELL
echo "==================================="
echo $0
echo "==================================="
ps  -ef | grep $$ | grep -v grep
echo "==================================="
git --version
echo "==================================="
cmake --version
echo "==================================="
pwd
echo "==================================="
printenv
echo "==================================="
ls -la
echo "==================================="
BRANCH_NAME="master"

export IMAGE_NAME="scorum/blockchain:$BRANCH_NAME"

echo "run docker"

docker build -t=$IMAGE_NAME .
