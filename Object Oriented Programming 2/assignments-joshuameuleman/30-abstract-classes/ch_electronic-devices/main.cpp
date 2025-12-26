#include <iostream>
#include <vector>

#include "ElectronicDevice.h"
#include "Laptop.h"
#include "Smartphone.h"
#include "Tablet.h"

int main() {
    std::vector<ElectronicDevice*> devices;

    // Create two laptops
    devices.push_back(new Laptop("Dell", "XPS13", "Windows 11", 13.3, 16, 512));
    devices.push_back(new Laptop("Lenovo", "ThinkPad X1", "Windows 11", 14.0, 16, 256));

    // Create two smartphones
    devices.push_back(new Smartphone("Apple", "iPhone 14", "iOS", 6.1, 6, 3200, "TelcoA"));
    devices.push_back(new Smartphone("Samsung", "Galaxy S22", "Android", 6.2, 8, 4000, "TelcoB"));

    // Create two tablets
    devices.push_back(new Tablet("Apple", "iPad Air", "iPadOS", 10.9, 8, 7600));
    devices.push_back(new Tablet("Samsung", "Galaxy Tab", "Android", 11.0, 6, 7000));

    // Iterate and perform basic actions
    for (size_t i = 0; i < devices.size(); ++i) {
        ElectronicDevice* dev = devices[i];
        dev->start();
        dev->showInfo();

        // Try derived-specific actions via dynamic_cast
        if (Laptop* lp = dynamic_cast<Laptop*>(dev)) {
            lp->installSoftware(50); // install 50 GB software
        }

        if (Smartphone* sp = dynamic_cast<Smartphone*>(dev)) {
            sp->makeCall(30); // 30-minute call
            sp->chargeBattery(500);
        }

        if (Tablet* tb = dynamic_cast<Tablet*>(dev)) {
            tb->watchMovie(120); // 2-hour movie
            tb->chargeBattery(1000);
        }

        dev->shutdown();
        std::cout << "---\n";
    }

    // cleanup
    for (ElectronicDevice* p : devices) delete p;

    return 0;
}
