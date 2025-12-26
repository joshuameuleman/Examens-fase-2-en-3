#pragma once

#include "ElectronicDevice.h"

class Tablet : public ElectronicDevice {
private:
    int battery_mAh_ = 0;
    int maxBattery_mAh_ = 0;
    const int lowBatteryThreshold_mAh_ = 300;

public:
    Tablet(const std::string& brand,
           const std::string& model,
           const std::string& os,
           double screenSize,
           int memoryGB,
           int battery_mAh);

    void start() const override;
    void showInfo() const override;
    void shutdown() const override;

    std::string deviceType() const override { return "Tablet"; }

    void chargeBattery(int amount_mAh);
    void watchMovie(int minutes);
};
