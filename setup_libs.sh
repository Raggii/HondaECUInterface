#!/bin/bash

# Update package lists
echo "Updating package lists..."
sudo apt-get update

# Install libsdl2-dev
echo "Installing libsdl2-dev..."
sudo apt-get install -y libsdl2-dev

# Check if the libs directory exists
if [ ! -d "libs" ]; then
    echo "Error: 'libs' directory does not exist. Please create it first."
    exit 1
fi

# Check if LVGL is already installed
if [ -d "libs/lvgl" ]; then
    echo "LVGL is already installed in 'libs/lvgl'. Skipping clone."
else
    # Clone LVGL into the libs directory
    echo "Cloning LVGL into the libs directory..."
    git clone --branch v8.3.0 https://github.com/lvgl/lvgl.git libs/lvgl

    # Check if the cloning was successful
    if [ $? -eq 0 ]; then
        echo "LVGL successfully cloned into 'libs/lvgl'."
    else
        echo "Error: Failed to clone LVGL."
        exit 1
    fi
fi

# Check if lv_drivers is already installed
if [ -d "libs/lv_drivers" ]; then
    echo "lv_drivers is already installed in 'libs/lv_drivers'. Skipping clone."
else
    # Clone lv_drivers into the libs directory
    echo "Cloning lv_drivers into the libs directory..."
    git clone --branch v8.3.0 https://github.com/lvgl/lv_drivers.git libs/lv_drivers

    # Check if the cloning was successful
    if [ $? -eq 0 ]; then
        echo "lv_drivers successfully cloned into 'libs/lv_drivers'."
    else
        echo "Error: Failed to clone lv_drivers."
        exit 1
    fi
fi
