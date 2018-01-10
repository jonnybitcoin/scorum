#!/bin/bash

BRANCH_NAME="master"

export IMAGE_NAME="scorum/blockchain:$BRANCH_NAME"

docker build -t=$IMAGE_NAME .
