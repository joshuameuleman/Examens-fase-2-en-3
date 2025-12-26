#include "Smartphone.h"
#include <iostream>

Smartphone::Smartphone(const std::string& brand,
                       const std::string& model,
                       const std::string& os,
                       double screenSize,
                       int memoryGB,
                       int battery_mAh,
                       const std::string& provider)
    : ElectronicDevice(brand, model, os, screenSize, memoryGB), battery_mAh_(battery_mAh), maxBattery_mAh_(battery_mAh), provider_(provider)
{
}

void Smartphone::start() const {
    std::cout << "The " << deviceType() << " " << brand_ << " " << model_ << " is starting up." << std::endl;
}

void Smartphone::showInfo() const {
    std::cout << "Type: " << deviceType() << "\n"
              << "Brand: " << brand_ << "\n"
              << "Model: " << model_ << "\n"
              << "OS: " << os_ << "\n"
              << "Screen: " << screenSize_ << " inches\n"
              << "Memory: " << memoryGB_ << " GB\n"
              << "Battery: " << battery_mAh_ << " mAh (max " << maxBattery_mAh_ << ")\n"
              << "Provider: " << provider_ << "\n";
}

void Smartphone::shutdown() const {
    std::cout << "The " << deviceType() << " " << brand_ << " " << model_ << " is shutting down." << std::endl;
}

void Smartphone::chargeBattery(int amount_mAh) {
    if (amount_mAh <= 0) return;
    battery_mAh_ += amount_mAh;
    if (battery_mAh_ >= maxBattery_mAh_) {
        battery_mAh_ = maxBattery_mAh_;
        std::cout << brand_ << " " << model_ << " is fully charged (" << battery_mAh_ << " mAh)." << std::endl;
    } else {
        std::cout << brand_ << " " << model_ << " charged to " << battery_mAh_ << " mAh." << std::endl;
    }
}

void Smartphone::makeCall(int durationMinutes) {
    if (durationMinutes <= 0) return;
    // Simple model: each minute costs 5 mAh
    int cost = durationMinutes * 5;
    battery_mAh_ -= cost;
    if (battery_mAh_ < 0) battery_mAh_ = 0;
    std::cout << brand_ << " " << model_ << " made a call for " << durationMinutes << " minutes, battery now " << battery_mAh_ << " mAh." << std::endl;
    if (battery_mAh_ <= lowBatteryThreshold_mAh_) {
        std::cout << "Warning: battery is getting low (" << battery_mAh_ << " mAh)." << std::endl;
    }
}
