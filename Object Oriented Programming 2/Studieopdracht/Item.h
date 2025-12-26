#pragma once
/*
    Basis C++ syntax (kort) — nuttig bij lezen van headers:
    - `T* p` : pointer naar T — bevat een geheugenadres, kan nullptr zijn.
    - `T& r` : reference naar T — alias, moet bij init gebonden worden, niet null.
    - `const` : maakt iets onveranderlijk (bijv. `const T&` of `void f() const`).
    - `virtual` : maakt een methode polymorf; `= 0` maakt het een pure virtual method (abstract).
    - `override` : geeft aan dat een afgeleide methode een virtuele basismethode overschrijft.
    - `~Class() = default;` : vraag de compiler om de standaard destructor te genereren.
*/

class Item
{
public:
    Item() = default;

    virtual ~Item()=default;
    
    // Pure virtual method: print human-readable info about the item.
    // Subclasses (Weapon, Potion, ...) must implement this.
    virtual void printInfo() const = 0;

    // Pure virtual method: return a numeric value for the item.
    // This can represent price, score, or any metric depending on the game.
    virtual double value() const = 0;
};

/*
Syntax notes (short):
 - `virtual`: marks a method as polymorphic; calls use the dynamic type at runtime.
 - `= 0` after a virtual method makes it a "pure virtual" method: the class is abstract
     (cannot be instantiated) and derived classes must implement that method.
 - `const` at the end of a member function (e.g. `printInfo() const`) means the
     method does not modify the object's observable state.
 - `~Item() = default;` asks the compiler to generate the default destructor.
     When a base class destructor is virtual, deleting derived objects through
     a base pointer is safe.
*/


