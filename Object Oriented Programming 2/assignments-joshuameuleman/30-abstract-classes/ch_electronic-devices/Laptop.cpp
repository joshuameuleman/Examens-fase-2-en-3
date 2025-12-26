#include "Laptop.h"
#include <iostream>

Laptop::Laptop(const std::string& brand,
               const std::string& model,
               const std::string& os,
               double screenSize,
               int memoryGB,
               int storageGB)
    : ElectronicDevice(brand, model, os, screenSize, memoryGB), storageGB_(storageGB)
{
}

void Laptop::start() const {
    std::cout << "The " << deviceType() << " " << brand_ << " " << model_ << " is starting up." << std::endl;
}

void Laptop::showInfo() const {
    std::cout << "Type: " << deviceType() << "\n"
              << "Brand: " << brand_ << "\n"
              << "Model: " << model_ << "\n"
              << "OS: " << os_ << "\n"
              << "Screen: " << screenSize_ << " inches\n"
              << "Memory: " << memoryGB_ << " GB\n"
              << "Storage: " << storageGB_ << " GB\n";
}

void Laptop::shutdown() const {
    std::cout << "The " << deviceType() << " " << brand_ << " " << model_ << " is shutting down." << std::endl;
}

void Laptop::installSoftware(int sizeGB) {
    std::cout << "Installing software of size " << sizeGB << " GB on " << brand_ << " " << model_ << "...\n";
    storageGB_ -= sizeGB;
    if (storageGB_ < storageWarningThreshold_) {
        std::cout << "Warning: remaining storage (" << storageGB_ << " GB) is below threshold!" << std::endl;
    } else {
        std::cout << "Install complete. Remaining storage: " << storageGB_ << " GB" << std::endl;
    }
}
