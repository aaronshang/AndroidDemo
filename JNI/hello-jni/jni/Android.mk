#*************************** EXPAT LIBRARY BEGIN ****************************************************************
LOCAL_PATH:= $(call my-dir)

# expat lib, which will be built statically
#

include $(CLEAR_VARS)

LOCAL_MODULE    := hellojni

LOCAL_C_INCLUDES := $(LOCAL_PATH)/

LOCAL_SRC_FILES := ./com_sk_hellojni_HelloJni.cpp

					
LOCAL_CPPFLAGS +=  -D_ANDROID
LOCAL_CPPFLAGS +=  -fexceptions
LOCAL_LDLIBS :=  -L$(SYSROOT)/usr/lib -ldl -llog -lz 

include $(BUILD_SHARED_LIBRARY)
