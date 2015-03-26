LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDLIBS := -llog

LOCAL_MODULE    := MyApp

LOCAL_SRC_FILES := AndroidClient.cpp ../../src/Personnage.cpp ../../src/Portee.cpp ../../src/Sort.cpp ../../src/SortVisuel.cpp ../../src/State.cpp ../../src/TextVisuel.cpp ../../src/formes.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include

LOCAL_SHARED_LIBRARIES += sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main


include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)

