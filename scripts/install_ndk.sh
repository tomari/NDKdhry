#!/bin/bash
source scripts/sdkpath.sh
set -e
DEPS="$NDK_HOME/installed-dependencies"

if [ ! -e "$DEPS" ]; then
	if [ ! -d "$NDK_HOME" ] ; then mkdir "$NDK_HOME" ; fi
	cd "$NDK_HOME"
	echo "Downloading NDK..."
	curl -g -o ndk.zip https://dl.google.com/android/repository/android-ndk-r16b-linux-x86_64.zip
	unzip -o -q ndk.zip
	echo "Installed Android NDK at $NDK_HOME"
	touch "$DEPS"
	rm ndk.zip
fi

sdkmanager "cmake;3.6.4111459"

