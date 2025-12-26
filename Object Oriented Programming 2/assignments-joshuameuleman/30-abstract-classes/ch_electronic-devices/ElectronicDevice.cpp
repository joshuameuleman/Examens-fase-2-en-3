#include "ElectronicDevice.h"

ElectronicDevice::ElectronicDevice(const std::string& brand,
                                   const std::string& model,
                                   const std::string& os,
                                   double screenSize,
                                   int memoryGB)
    : brand_(brand), model_(model), os_(os), screenSize_(screenSize), memoryGB_(memoryGB)
{
}
