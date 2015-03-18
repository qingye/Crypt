LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := base64
LOCAL_SRC_FILES := base64/base64.cpp
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/base64
LOCAL_EXPORT_LDLIBS := -llog
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := des
LOCAL_SRC_FILES := des/des.cpp
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/des
LOCAL_EXPORT_LDLIBS := -llog
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := zlib
LOCAL_SRC_FILES := zlib/adler32.c zlib/compress.c zlib/crc32.c zlib/deflate.c\
                   zlib/gzclose.c zlib/gzlib.c zlib/gzread.c zlib/gzwrite.c\
				   zlib/infback.c zlib/inffast.c zlib/inflate.c zlib/inftrees.c\
				   zlib/trees.c zlib/uncompr.c zlib/zutil.c
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/zlib
LOCAL_EXPORT_LDLIBS := -llog
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := crypt
LOCAL_SRC_FILES := jniNative.cpp Crypt.cpp
LOCAL_STATIC_LIBRARIES := base64 des zlib
LOCAL_LDLIBS    := -lm -llog
include $(BUILD_SHARED_LIBRARY)
