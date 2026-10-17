#
# SPDX-FileCopyrightText: The LineageOS Project
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit_only.mk)


# Inherit from yupei device
$(call inherit-product, device/xiaomi/yupei/device.mk)

PRODUCT_NAME := custom_yupei
PRODUCT_DEVICE := yupei
PRODUCT_MANUFACTURER := Xiaomi
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := 25097RP43G

PRODUCT_SYSTEM_NAME := yupei_global
PRODUCT_SYSTEM_DEVICE := yupei

PRODUCT_BUILD_PROP_OVERRIDES += \
    BuildDesc="yupei_global-user 15 AQ3A.250226.002 OS3.0.303.0.WPZINXM release-keys" \
    BuildFingerprint=Xiaomi/yupei_global/yupei:15/AQ3A.250226.002/OS3.0.303.0.WPZINXM:user/release-keys \
    DeviceName=$(PRODUCT_SYSTEM_DEVICE) \
    DeviceProduct=$(PRODUCT_SYSTEM_NAME)

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi
