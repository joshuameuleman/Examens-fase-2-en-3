#include "Tablet.h"
#include <iostream>

Tablet::Tablet(const std::string& brand,
               const std::string& model,
               const std::string& os,
               double screenSize,
               int memoryGB,
               int battery_mAh)
    : ElectronicDevice(brand, model, os, screenSize, memoryGB), battery_mAh_(battery_mAh), maxBattery_mAh_(battery_mAh)
{
}

void Tablet::start() const {
    std::cout << "The " << deviceType() << " " << brand_ << " " << model_ << " is starting up." << std::endl;
}

void Tablet::showInfo() const {
    std::cout << "Type: " << deviceType() << "\n"
              << "Brand: " << brand_ << "\n"
              << "Model: " << model_ << "\n"
              << "OS: " << os_ << "\n"
              << "Screen: " << screenSize_ << " inches\n"
              << "Memory: " << memoryGB_ << " GB\n"
              << "Battery: " << battery_mAh_ << " mAh (max " << maxBattery_mAh_ << ")\n";
}

void Tablet::shutdown() const {
    std::cout << "The " << deviceType() << " " << brand_ << " " << model_ << " is shutting down." << std::endl;
}

void Tablet::chargeBattery(int amount_mAh) {
    if (amount_mAh <= 0) return;
    battery_mAh_ += amount_mAh;
    if (battery_mAh_ >= maxBattery_mAh_) {
        battery_mAh_ = maxBattery_mAh_;
        std::cout << brand_ << " " << model_ << " is fully charged (" << battery_mAh_ << " mAh)." << std::endl;
    } else {
        std::cout << brand_ << " " << model_ << " charged to " << battery_mAh_ << " mAh." << std::endl;
    }
}

void Tablet::watchMovie(int minutes) {
    if (minutes <= 0) return;
    // Assume 10 mAh per minute for movie playback
    int cost = minutes * 10;
    battery_mAh_ -= cost;
    if (battery_mAh_ < 0) battery_mAh_ = 0;
    std::cout << brand_ << " " << model_ << " watched a movie for " << minutes << " minutes, battery now " << battery_mAh_ << " mAh." << std::endl;
    if (battery_mAh_ <= lowBatteryThreshold_mAh_) {
        std::cout << "Warning: battery is getting low (" << battery_mAh_ << " mAh)." << std::endl;
    }
}
