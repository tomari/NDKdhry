# NDKDhryV7

Dhrystone benchmark in C language, compiled for Android devices.
Uses Android NDK to run Dhrystone benchmark natively on processor.

## Features (v5)
* Option to turn backlight off during running the benchmark (useful when measuring electrical power consumption)
* Add support for arm64-v8a, x86_64 and mips64 architectures
* Multi-process Dhrystone -- run multiple dhrystone processes simultaneously.

## Supported Devices
Runs on Android 1.6+
Tested against Android L emulator and Android 4.1 Tablet.

Supported processors are arm64-v8a, x86_64, mips64, armeabi-v7a,
armeabi, x86 and mips.
Default compiler flags are: "-O3"
Binary is built using Android NDK R10.

## How to compile
* run ndk-build script included in the Android NDK in jni directory
* compile project in Eclipse

## License
public domain

