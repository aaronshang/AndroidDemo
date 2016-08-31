#*************************** EXPAT LIBRARY BEGIN ****************************************************************
LOCAL_PATH:= $(call my-dir)

# expat lib, which will be built statically
#

include $(CLEAR_VARS)

LOCAL_MODULE    := writefile

LOCAL_C_INCLUDES := $(LOCAL_PATH)/

LOCAL_SRC_FILES := ./Log.cpp  ./LibWriteFile.cpp ./com_example_test_CreateFile.cpp

					
LOCAL_CPPFLAGS +=  -D_ANDROID
LOCAL_CPPFLAGS +=  -fexceptions
LOCAL_LDLIBS :=  -L$(SYSROOT)/usr/lib -ldl -llog -lz -pthread

include $(BUILD_SHARED_LIBRARY)
