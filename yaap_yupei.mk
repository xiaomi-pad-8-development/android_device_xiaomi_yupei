#
# SPDX-FileCopyrightText: The LineageOS Project
# SPDX-FileCopyrightText: 2026 Yet Another AOSP Project
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit_only.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base.mk)

# YAAP Flags
TARGET_SUPPORTS_64_BIT_APPS := true
TARGET_ENABLE_BLUR := true

# Inherit some common YAAP stuff.
$(call inherit-product, vendor/yaap/config/common_full_tablet_wifionly.mk)

# Inherit from yupei device
$(call inherit-product, device/xiaomi/yupei/device.mk)

PRODUCT_NAME := yaap_yupei
PRODUCT_DEVICE := yupei
PRODUCT_MANUFACTURER := Xiaomi
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := 25097RP43C

PRODUCT_SYSTEM_NAME := yupei_global
PRODUCT_SYSTEM_DEVICE := yupei

# Boot animation
TARGET_SCREEN_HEIGHT := 3200
TARGET_SCREEN_WIDTH := 2136

PRODUCT_BUILD_PROP_OVERRIDES += \
    BuildDesc="yupei_global-user 15 AQ3A.250226.002 OS3.0.303.0.WPZINXM release-keys" \
    BuildFingerprint=Xiaomi/yupei_global/yupei:15/AQ3A.250226.002/OS3.0.303.0.WPZINXM:user/release-keys \
    DeviceName=$(PRODUCT_SYSTEM_DEVICE) \
    DeviceProduct=$(PRODUCT_SYSTEM_NAME)

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi
