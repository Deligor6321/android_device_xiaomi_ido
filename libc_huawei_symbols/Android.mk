# Copyright (C) 2015 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    hw_cutils.c \
    hw_exif.c \
    hw_gps.c \
    hw_log.c \
    hw_widevine.c

LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)
LOCAL_MODULE := libc_huawei_symbols
LOCAL_MODULE_TAGS := optional

# Debugging (uncomment to enable)
# LOCAL_CFLAGS += -DHW_LIBC_DEBUG
# LOCAL_WHOLE_STATIC_LIBRARIES := liblog

include $(BUILD_STATIC_LIBRARY)