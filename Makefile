ifeq ($(THEOS_PACKAGE_SCHEME),rootless)
TARGET := iphone:clang:16.5:15.0
else
TARGET := iphone:clang:16.5:16.0
endif

INSTALL_TARGET_PROCESSES = SpringBoard Preferences

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = CCSupport
CCSupport_CFLAGS = -fobjc-arc -D DISABLE_ROOTLESS_COMPAT_WARNING -I$(THEOS_PROJECT_DIR)/include
CCSupport_FILES = $(wildcard *.xm *.m)
CCSupport_PRIVATE_FRAMEWORKS = MobileIcons Preferences ControlCenterUI ControlCenterServices ControlCenterUIKit

ifneq ($(THEOS_PACKAGE_SCHEME),rootless)
CCSupport_CFLAGS += -D XINA_SUPPORT=1
endif

include $(THEOS_MAKE_PATH)/tweak.mk

SUBPROJECTS += HomeProvider
include $(THEOS_MAKE_PATH)/aggregate.mk
