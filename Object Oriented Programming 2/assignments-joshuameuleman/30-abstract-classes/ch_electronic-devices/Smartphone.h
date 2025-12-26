#pragma once

#include "ElectronicDevice.h"
#include <string>

class Smartphone : public ElectronicDevice {
private:
    int battery_mAh_ = 0; // current charge
    int maxBattery_mAh_ = 0;
    std::string provider_;
    const int lowBatteryThreshold_mAh_ = 300; // mAh threshold for low battery message

public:
    Smartphone(const std::string& brand,
               const std::string& model,
               const std::string& os,
               double screenSize,
               int memoryGB,
               int battery_mAh,
               const std::string& provider);

    void start() const override;
    void showInfo() const override;
    void shutdown() const override;

    std::string deviceType() const override { return "Smartphone"; }

    void chargeBattery(int amount_mAh);
    void makeCall(int durationMinutes);
};
