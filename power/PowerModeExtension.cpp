/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <aidl/android/hardware/power/BnPower.h>
#include <android-base/logging.h>
#include <android-base/unique_fd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

namespace aidl {
namespace google {
namespace hardware {
namespace power {
namespace impl {
namespace pixel {

using ::aidl::android::hardware::power::Mode;

namespace {

// The touch features of the panel are set through the xiaomi touch device.
constexpr char kTouchDevice[] = "/dev/xiaomi-touch";
constexpr int kTouchId = 0;
constexpr int kSelectTouchIdCmd = 3;
constexpr int kCommonDataCmd = 0;
constexpr uint8_t kSetCurValue = 0;
constexpr uint16_t kDoubleTapMode = 14;

struct TouchCommonData {
    int8_t touch_id;
    uint8_t cmd;
    uint16_t mode;
    uint16_t data_len;
    int32_t data_buf[256];
};

bool setDoubleTap(bool enabled) {
    ::android::base::unique_fd fd(open(kTouchDevice, O_RDWR | O_CLOEXEC));
    if (fd < 0) {
        PLOG(ERROR) << "Failed to open " << kTouchDevice;
        return false;
    }

    if (ioctl(fd, _IO('T', kSelectTouchIdCmd), kTouchId) < 0) {
        PLOG(ERROR) << "Failed to select touch " << kTouchId;
        return false;
    }

    TouchCommonData data = {
            .touch_id = kTouchId,
            .cmd = kSetCurValue,
            .mode = kDoubleTapMode,
            .data_len = 1,
    };
    data.data_buf[0] = enabled;

    if (ioctl(fd, _IOW('T', kCommonDataCmd, TouchCommonData), &data) < 0) {
        PLOG(ERROR) << "Failed to set double tap to " << enabled;
        return false;
    }

    return true;
}

}  // namespace

bool isDeviceSpecificModeSupported(Mode type, bool* _aidl_return) {
    if (type != Mode::DOUBLE_TAP_TO_WAKE)
        return false;

    *_aidl_return = true;
    return true;
}

bool setDeviceSpecificMode(Mode type, bool enabled) {
    if (type != Mode::DOUBLE_TAP_TO_WAKE)
        return false;

    setDoubleTap(enabled);
    return true;
}

}  // namespace pixel
}  // namespace impl
}  // namespace power
}  // namespace hardware
}  // namespace google
}  // namespace aidl
