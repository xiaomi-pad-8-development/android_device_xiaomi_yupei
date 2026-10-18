/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <aidl/xiaomi/system/hypsys/common/BnHypSysSsi.h>
#include <aidl/xiaomi/system/hypsys/common/BnHypSysSsiIntl.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include <string>
#include <vector>

using ::aidl::xiaomi::system::hypsys::common::BnHypSysSsi;
using ::aidl::xiaomi::system::hypsys::common::BnHypSysSsiIntl;
using ::ndk::ScopedAStatus;
using ::ndk::SharedRefBase;

/*
 * Xiaomi's blobs only report analytics events into this service, so every call
 * is accepted and dropped.
 */
struct HypSysSsiService : public BnHypSysSsi {
    ScopedAStatus reportSimpleEvent(int32_t, const std::string&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus reportEventV2(const std::string&, const std::string&, const std::string&,
                                bool) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus reportNativeFeatureEvent(const std::string&, const std::string&,
                                           const std::string&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus appCaptureLog(const std::string&, const std::string&, const std::string&,
                                const std::string&) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus reportEventsV2(const std::string&, const std::vector<std::string>&,
                                 const std::string&, bool) override {
        return ScopedAStatus::ok();
    }
    ScopedAStatus reportOneTrackEvent(const std::string&, const std::string&, const std::string&,
                                      int32_t, int32_t* _aidl_return) override {
        *_aidl_return = 0;
        return ScopedAStatus::ok();
    }
    ScopedAStatus reportOneTrackEvents(const std::string&, const std::string&,
                                       std::vector<std::string>*, int32_t,
                                       int32_t* _aidl_return) override {
        *_aidl_return = 0;
        return ScopedAStatus::ok();
    }
};

struct HypSysSsiIntlService : public BnHypSysSsiIntl {
    ScopedAStatus transferMessage(const std::string&, const std::string&) override {
        return ScopedAStatus::ok();
    }
};

template <typename Service>
static bool addService() {
    auto service = SharedRefBase::make<Service>();
    const std::string instance = std::string(Service::descriptor) + "/default";
    return AServiceManager_addService(service->asBinder().get(), instance.c_str()) == STATUS_OK;
}

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);

    if (!addService<HypSysSsiService>() || !addService<HypSysSsiIntlService>()) {
        return 1;
    }

    ABinderProcess_joinThreadPool();
    return 1;  // should not be reached
}
