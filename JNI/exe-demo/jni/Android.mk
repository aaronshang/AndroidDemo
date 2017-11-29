LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= UBDllLoad.cpp main.cpp

LOCAL_MODULE:= kdemo
LOCAL_CFLAGS += -pie -fPIE -fPIC
LOCAL_LDFLAGS += -pie -fPIE -fPIC
LOCAL_CFLAGS += -fvisibility=hidden  -D__LINUX__ -D__DebugModel__ -D__Android__

LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_LDLIBS += -llog  

include $(BUILD_EXECUTABLE)
