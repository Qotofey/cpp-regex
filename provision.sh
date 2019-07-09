#!/bin/bash

PROJECT_NAME="calc"
USERNAME="vagrant"

apt update -y && apt list --upgradable
apt install -y clang make cmake python3-pip

pip3 install conan

echo -e "That's all!"