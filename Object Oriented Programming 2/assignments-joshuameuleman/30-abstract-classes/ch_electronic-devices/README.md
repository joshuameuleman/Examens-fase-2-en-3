# Electronic Devices

## Objective

Create an inheritance hierarchy to manage different types of electronic devices, such as **laptops**, **smartphones**, and **tablets**.

Each type of device has common and specific data attributes and actions.

## Device Specifications

### Laptop

**Attributes:**
- Brand
- Model
- Operating System
- Screen Size (in inches)
- Memory (in GB)
- Storage Capacity (in GB)

**Actions:**
- **Basic actions** (*see below*)
- **Install software**: reduce the available storage by the size of the software in GB. If the remaining storage goes below a minimum threshold, print a warning that the storage is insufficient.

### Smartphone

**Attributes:**
- Brand
- Model
- Operating System
- Screen Size (in inches)
- Memory (in GB)
- Battery Capacity (in mAh)
- Mobile Provider

**Actions:**
- **Basic actions** (*see below*)
- **Charge battery**: increase the battery capacity by a given amount of mAh. Print a message when the battery is fully charged.
- **Make call**: decrease battery capacity when calling. Print a message when the battery is getting low.

### Tablet

**Attributes:**
- Brand
- Model
- Operating System
- Screen Size (in inches)
- Memory (in GB)
- Battery Capacity (in mAh)

**Actions:**
- **Basic actions** (*see below*)
- **Charge battery**: increase the battery capacity by a given amount of mAh. Print a message when the battery is fully charged.
- **Watch movie**: decrease battery capacity during movie playback. Print a message when the battery is getting low.

## Basic Actions \(*Applicable to All Devices*\)

- **Start**: print a message like  
  `"The [device type] [brand] [model] is starting up."`
- **Show info**: display all relevant device data (brand, model, OS, memory, screen size, storage/battery capacity, etc.)
- **Shut down**: print a message like  
  `"The [device type] [brand] [model] is shutting down."`

## Notes and Requirements

- **Avoid duplicate code** as much as possible by using **inheritance** and **polymorphism**.
- Consider using **abstract base classes** and/or **interfaces** for shared behavior.
- Design your structure so that additional categories like **e-readers** or **smartwatches** can be added later with minimal changes.
- In the `main()` function:
  - Create **at least two objects per device type**.
  - Optionally, allow dynamic creation based on user input (not mandatory).
  - Store all device objects in a `std::vector` of base class pointers.
  - Iterate over the list and:
    - Perform basic actions (`start`, `show info`, `shut down`)
    - Use **dynamic casting** to invoke specific actions based on the actual device type.
- The list of objects is executed polymorphically, this means that at compile-time you can only execute methods of the base object. If you want to treat the object as the specific object and then call specific methods, you will have to downcast the object.

```cpp
DerivedClass* d = dynamic_cast<DerivedClass*>(listOfBaseClassObjects[index]);
if (d != nullptr) {
    // Call derived-class-specific methods...
}
