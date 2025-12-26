#pragma once

#include <string>

class ElectronicDevice {
protected:
    std::string brand_;
    std::string model_;
    std::string os_;
    double screenSize_ = 0.0; // inches
    int memoryGB_ = 0;

public:
    ElectronicDevice(const std::string& brand,
                     const std::string& model,
                     const std::string& os,
                     double screenSize,
                     int memoryGB);
    virtual ~ElectronicDevice() = default;

    virtual void start() const = 0;
    virtual void showInfo() const = 0;
    virtual void shutdown() const = 0;

    // Helpful to identify the concrete type in messages
    virtual std::string deviceType() const = 0;
};
