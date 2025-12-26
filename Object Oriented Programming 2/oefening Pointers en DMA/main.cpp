#include "SensorArray.h"
#include <iostream>
using namespace std;
using namespace Sensors;
int main ()
{
    cout << "Enter number of sensors: ";
    int n;
    cin >> n;
    cout << "\n === stack based object === \n" << endl;
    SensorArray sensorArray(n); // stack based object
    sensorArray.Fillvalues();
    cout << "Average: " << sensorArray.Average() << endl;
    cout << "Max: " << sensorArray.Max() <<  endl;
    cout << "Min: " << sensorArray.Min() <<  endl;
    sensorArray.Sort();
    double* alias = sensorArray.GetRawPointer();
    sensorArray.AddOffset(5.0, alias);
    cout << "After adding offset of 5.0, new Average: " << sensorArray.Average() << endl;
   
    //demonstrate pointer parameter passing 
    cout<< "Passing pointer as parameter demonstration: "<< endl;
    double* firstValue=sensorArray.GetRawPointer();
    cout << "First value before offset: " << *firstValue << endl;

    //heap based object
    cout << "\n === heap based object === \n" << endl;
    SensorArray* heapArray = new SensorArray(n); // heap based object
    heapArray->Fillvalues();
    cout << "Average: " << heapArray->Average() << endl;
    cout << "Max: " << heapArray->Max() <<  endl;
    cout << "Min: " << heapArray->Min() <<  endl;
    heapArray->Sort();
    double* heapAlias = heapArray->GetRawPointer();
    heapArray->AddOffset(10.0, heapAlias);
    cout << "After adding offset of 10.0, new Average: " << heapArray->Average() << endl;
    //demonstrate pointer parameter passing
    double* firstHeapValue=heapArray->GetRawPointer();
    cout << "First value before offset: " << *firstHeapValue << endl;
    delete heapArray; // free heap memory
    return 0;

}