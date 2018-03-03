add_library (
	ndk1
	SHARED

	src/main/jni/dhry21a.c
	src/main/jni/dhry21b.c
	src/main/jni/native.c
	src/main/jni/timers.c
)
set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

