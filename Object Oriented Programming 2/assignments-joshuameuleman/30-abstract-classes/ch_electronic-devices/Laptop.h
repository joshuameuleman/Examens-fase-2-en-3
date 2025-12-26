#pragma once

#include "ElectronicDevice.h"
#include <string>

class Laptop : public ElectronicDevice {
private:
    int storageGB_ = 0;
    const int storageWarningThreshold_ = 10; // GB

public:
    Laptop(const std::string& brand,
           const std::string& model,
           const std::string& os,
           double screenSize,
           int memoryGB,
           int storageGB);

    void start() const override;
    void showInfo() const override;
    void shutdown() const override;

    std::string deviceType() const override { return "Laptop"; }

    void installSoftware(int sizeGB);
};
