# This project has been migrated to https://gitlab.com/tomari/NDKdhry

# NDKDhryV7

[![CircleCI](https://circleci.com/gh/tomari/NDKdhry.svg?style=svg)](https://circleci.com/gh/tomari/NDKdhry)

Dhrystone benchmark in C language, compiled for Android devices.
Uses Android NDK to run Dhrystone benchmark natively on processor.
Processor cores on which to run the benchmark can be specified (useful when you have multiple types of processor cores on a device).

## Changes (v7)
* Migrate IDE to Android Studio -- supports API>11 until the APP_PLATFORM bug in Android Studio is fixed
* Show cpuinfo on startup
* Allow user to choose processor cores on which to run the benchmark
* Add clear log and share log menu items

## Changes (v6)
* Show compiler version and word length on startup
* Apply Material theme on Android 5.1+ (5.0 has a bug where it's hard to work around)

## Changes (v5)
* Option to turn backlight off during running the benchmark (useful when measuring electrical power consumption)
* Add support for arm64-v8a, x86_64 and mips64 architectures
* Multi-process Dhrystone -- run multiple dhrystone processes simultaneously.

## Supported Devices
Runs on Android 3+
Tested on Android 6 emulator and Android 5.1 Tablet.

Supported processors are arm64-v8a, x86_64, mips64, armeabi-v7a,
armeabi, x86 and mips.
Default compiler flags are: "-O3"
Binary is built using Android NDK R10e.

## How to compile
* compile project in Android Studio

## License
public domain

