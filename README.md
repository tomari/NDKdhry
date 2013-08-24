# NDKDhryV7

Dhrystone benchmark in C language, compiled for Android devices.
Uses Android NDK to run Dhrystone benchmark natively on processor.

## Supported Devices
Requires Android 2.2+ due to permission constraints.
Runs on Android 1.6+ if AndroidManifest.xml is modified:
```
 android:minSdkVersion="4"
```

Supported processors are armeabi-v7a, x86,
armeabi and mips.
Default compiler flags are: "-O3"

Tested on Sony Xperia Tablet Z running Android 4.1.2.

## How to compile
* put android-support-v4.jar into libs directory
* run ndk-build script included in the Android NDK in jni directory
* compile project in Eclipse

## License
public domain

