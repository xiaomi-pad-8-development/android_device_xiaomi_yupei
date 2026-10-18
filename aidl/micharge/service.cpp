/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <aidl/vendor/xiaomi/hardware/micharge/BnMiCharge.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include <string>

using ::aidl::vendor::xiaomi::hardware::micharge::BnMiCharge;
using ::aidl::vendor::xiaomi::hardware::micharge::IMiCharge;
using ::ndk::ScopedAStatus;

/*
 * Every method of the interface answers with an empty value, nothing on the
 * device reads charging state through it, but Xiaomi's blobs expect it to be
 * registered. The methods come in a handful of shapes, listed below.
 */

// std::string name()
#define MICHARGE_STRING_GETTERS(X) \
    X(getBatteryAuthentic)         \
    X(getBatteryCapacity)          \
    X(getBatteryChargeFull)        \
    X(getBatteryChargeType)        \
    X(getBatteryCycleCount)        \
    X(getBatteryIbat)              \
    X(getBatteryResistance)        \
    X(getBatterySoh)               \
    X(getBatteryTbat)              \
    X(getBatteryThermaLevel)       \
    X(getBatteryVbat)              \
    X(getBtTransferStartState)     \
    X(getCarChargingType)          \
    X(getChargingPowerMax)         \
    X(getCoolModeState)            \
    X(getFastChargeModeStatus)     \
    X(getInputSuspendState)        \
    X(getNightChargingState)       \
    X(getPSValue)                  \
    X(getPdApdoMax)                \
    X(getPdAuthentication)         \
    X(getQuickChargeType)          \
    X(getSBState)                  \
    X(getSocDecimal)               \
    X(getSocDecimalRate)           \
    X(getTxAdapt)                  \
    X(getUsbCurrent)               \
    X(getUsbVoltage)               \
    X(getWirelessChargingStatus)   \
    X(getWirelessFwStatus)         \
    X(getWirelessReverseStatus)

// std::string name(std::string key)
#define MICHARGE_KEYED_GETTERS(X) \
    X(getMiChargePath)            \
    X(getTypeCCommonInfo)         \
    X(getChargeCommonInfo)        \
    X(getBatteryCommonInfo)

// bool name()
#define MICHARGE_BOOL_GETTERS(X)        \
    X(isBatteryLifeFunctionSupported)   \
    X(isDPConnected)                    \
    X(isUSB32)                          \
    X(isWirelessChargingSupported)      \
    X(isWiressFwUpdateSupported)

// int name(std::string value)
#define MICHARGE_SETTERS(X)      \
    X(setBtState)                \
    X(setBtTransferStartState)   \
    X(setCoolModeState)          \
    X(setInputSuspendState)      \
    X(setNightChargingState)     \
    X(setRxCr)                   \
    X(setSBState)                \
    X(setSmCountReset)           \
    X(setUpdateWirelessFw)       \
    X(setWlsTxSpeed)

// int name(std::string key, std::string value)
#define MICHARGE_KEYED_SETTERS(X) \
    X(setMiChargePath)            \
    X(setTypeCCommonInfo)         \
    X(setChargeCommonInfo)        \
    X(setBatteryCommonInfo)

#define STRING_GETTER(name)                                                \
    ScopedAStatus name(std::string* _aidl_return) override {               \
        _aidl_return->clear();                                             \
        return ScopedAStatus::ok();                                        \
    }
#define KEYED_GETTER(name)                                                 \
    ScopedAStatus name(const std::string&, std::string* _aidl_return) override { \
        _aidl_return->clear();                                             \
        return ScopedAStatus::ok();                                        \
    }
#define BOOL_GETTER(name)                                                  \
    ScopedAStatus name(bool* _aidl_return) override {                      \
        *_aidl_return = false;                                             \
        return ScopedAStatus::ok();                                        \
    }
#define SETTER(name)                                                       \
    ScopedAStatus name(const std::string&, int32_t* _aidl_return) override { \
        *_aidl_return = 0;                                                 \
        return ScopedAStatus::ok();                                        \
    }
#define KEYED_SETTER(name)                                                 \
    ScopedAStatus name(const std::string&, const std::string&,             \
                       int32_t* _aidl_return) override {                   \
        *_aidl_return = 0;                                                 \
        return ScopedAStatus::ok();                                        \
    }

struct MiChargeService : public BnMiCharge {
    MICHARGE_STRING_GETTERS(STRING_GETTER)
    MICHARGE_KEYED_GETTERS(KEYED_GETTER)
    MICHARGE_BOOL_GETTERS(BOOL_GETTER)
    MICHARGE_SETTERS(SETTER)
    MICHARGE_KEYED_SETTERS(KEYED_SETTER)

    ScopedAStatus isFunctionSupported(const std::string&, bool* _aidl_return) override {
        *_aidl_return = false;
        return ScopedAStatus::ok();
    }

    ScopedAStatus setWirelessChargingEnabled(bool, int32_t* _aidl_return) override {
        *_aidl_return = 0;
        return ScopedAStatus::ok();
    }
};

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);

    auto service = ndk::SharedRefBase::make<MiChargeService>();
    const std::string instance = std::string(IMiCharge::descriptor) + "/default";
    if (AServiceManager_addService(service->asBinder().get(), instance.c_str()) != STATUS_OK) {
        return 1;
    }

    ABinderProcess_joinThreadPool();
    return 1;  // should not be reached
}
