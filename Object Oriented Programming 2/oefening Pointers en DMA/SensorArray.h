#pragma once

namespace Sensors{

class SensorArray{
    // attributes
    private: 
    double *values;
    int size;

    
    public:
    //methods
    void Fillvalues(); // fills the array with random values between 0 and 100
    double Average() const; // returns the average of the values in the array
    double Max() const; // returns the maximum value in the array
    double Min() const; // returns the minimum value in the array
    void Sort(); // sorts the array in ascending order
    double* GetRawPointer(); // returns the raw pointer to the array
    void AddOffset(double offset, double* ptr); // adds an offset to each value in the array using the raw pointer
    

    //constructor
     SensorArray(int size);
     ~SensorArray();
     

 };

}