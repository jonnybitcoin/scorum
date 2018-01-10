#!/bin/bash

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
