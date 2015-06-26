# Global path definitions for all demos

#Specify target architecture here or give as command line option
# allowed values Linux_x86, Linux_x64, D2, D3

TARGET_ARCH = Linux_x86

# Path to your installation of the VRmagic SDK 
# for D2 Platform: /your/path/to/VRmUsbCamDistributionForDevelopers-$(SDK_VERSION)
# for Linux_x86/x64 and D3: set SDK_VERSION to version you want to build against 
SDK_VERSION = 4.3.2
LIBVRMUSBCAM2_VERSION = 3.3.3.0
VM_LIB_VERSION = 1.0.1.0
VRM_DIR = /opt/vrmagic/sdk-$(SDK_VERSION)

#Only for D2 platform: Specify path to Code Sourcery Toolchain
D2_ARM_BUILD_SYSTEM = /opt/D2/arm_build_system/bin

############### DO NOT EDIT BELOW THIS LINE ###########

# Check Target Architecture

ALLOWED_ARCHS = Linux_x86 Linux_x64 D2 D3

ifndef TARGET_ARCH
  $(error Variable TARGET_ARCH must be set in Rules.make of on the command line! Allowed target architectures are: $(ALLOWED_ARCHS))
endif

_TARGET_ARCH := $(filter $(TARGET_ARCH),$(ALLOWED_ARCHS))

$(info Building for $(_TARGET_ARCH))

ifndef _TARGET_ARCH
  $(error "Variable TARGET_ARCH not set correctly! Possible target architectures: Linux_x86, Linux_x64, D2, D3")
endif


## Linux_x86
ifeq ($(_TARGET_ARCH), Linux_x86)
    VRMSDK_INSTALL_DIR = $(VRM_DIR)/x86/development_kit
    VRM_INCPATH = -I$(VRMSDK_INSTALL_DIR)/include -I$(VRMSDK_INSTALL_DIR)/vm_lib/include
    VRM_LIBPATH = -L$(VRMSDK_INSTALL_DIR)/lib -L$(VRMSDK_INSTALL_DIR)/vm_lib/lib
	CPP_WRAPPER_PATH = ../polarisation_detector/wrappers/c++
endif

## Linux_x64
ifeq ($(_TARGET_ARCH), Linux_x64)
    VRMSDK_INSTALL_DIR = $(VRM_DIR)/x64/development_kit
    VRM_INCPATH = -I$(VRMSDK_INSTALL_DIR)/include -I$(VRMSDK_INSTALL_DIR)/vm_lib/include
    VRM_LIBPATH = -L$(VRMSDK_INSTALL_DIR)/lib/ -L$(VRMSDK_INSTALL_DIR)/vm_lib/lib
	CPP_WRAPPER_PATH = ../polarisation_detector/wrappers/c++
endif

## D2
ifeq ($(_TARGET_ARCH), D2)
    VRMSDK_INSTALL_DIR = $(VRM_DIR)/D2/development_kit
    CROSS_COMPILE_PREFIX = $(D2_ARM_BUILD_SYSTEM)/arm-none-linux-gnueabi-
    VRM_INCPATH = -I$(VRMSDK_INSTALL_DIR)/include -I$(VRMSDK_INSTALL_DIR)/vm_lib/include
    VRM_LIBPATH = -L$(VRMSDK_INSTALL_DIR)/lib -L$(VRMSDK_INSTALL_DIR)/vm_lib/lib
    VRM_CFLAGS = -DD2_PLATFORM
endif

## D3
ifeq ($(_TARGET_ARCH), D3)
    VRMSDK_INSTALL_DIR = $(VRM_DIR)/D3/
    CROSS_COMPILE_PREFIX = arm-linux-gnueabihf-
    VRM_CROSS_BUILD_PATH=/usr/arm-linux-gnueabihf/vrmagic
	GST_INSTALL_PATH=$(VRM_CROSS_BUILD_PATH)
	CPP_WRAPPER_PATH = ../polarisation_detector/wrappers/c++

    VRM_INCPATH = -I/usr/arm-linux-gnueabihf/include \
    -I$(VRM_CROSS_BUILD_PATH)/usr/include \
    -I$(VRM_CROSS_BUILD_PATH)/usr/include/libvrmusbcam2-$(LIBVRMUSBCAM2_VERSION) \
    -I$(VRM_CROSS_BUILD_PATH)/usr/vm_lib-$(VM_LIB_VERSION)/include

    VRM_LIBPATH = -L/usr/arm-linux-gnueabihf/lib \
    -L$(VRM_CROSS_BUILD_PATH)/lib \
    -L$(VRM_CROSS_BUILD_PATH)/lib/arm-linux-gnueabihf \
    -L$(VRM_CROSS_BUILD_PATH)/usr/lib \
    -L$(VRM_CROSS_BUILD_PATH)/usr/lib/arm-linux-gnueabihf \
    -L$(VRM_CROSS_BUILD_PATH)/usr/lib/libvrmusbcam2-$(LIBVRMUSBCAM2_VERSION) \
    -L$(VRM_CROSS_BUILD_PATH)/usr/vm_lib-$(VM_LIB_VERSION)/lib

    VRM_LFLAGS = -Wl,--rpath-link=/usr/arm-linux-gnueabihf/lib:/usr/arm-linux-gnueabihf/vrmagic/lib/:/usr/arm-linux-gnueabihf/vrmagic/lib/arm-linux-gnueabihf:/usr/arm-linux-gnueabihf/vrmagic/usr/lib:/usr/arm-linux-gnueabihf/vrmagic/usr/lib/arm-linux-gnueabihf

    VRM_CFLAGS = -DD3_PLATFORM
endif
