#include "SensorArray.h"
#include <iostream>
#include <cstdlib>
using namespace std;

namespace Sensors{
    
    void SensorArray:: Fillvalues(){

      
        for(int i=0; i<size; i++){
            *(values+i) = (rand() % 10000)/100.0; // random value between 0 and 100

        }

    }
    double SensorArray:: Average() const{
        double sum =0.0;
        for(int i=0; i<size; i++){
            sum += *(values+i);
        }
        return sum/size;
    }
    double SensorArray:: Max() const{
        double maxVal = *(values);
        for(int i=1; i<size; i++){
            if(*(values+i) > maxVal){
                maxVal = *(values+i);
            }
        }
        return maxVal;
    }
    double SensorArray:: Min() const{
        double minVal = *(values);
        for(int i=1; i<size; i++){
            if(*(values+i) < minVal){
                minVal = *(values+i);
            }
        }
        return minVal;
    }
    void SensorArray:: Sort(){
        for(int i=0; i<size-1; i++){
            for(int j=0; j<size-i-1; j++){
                if(*(values+j) > *(values+j+1)){
                    double swap = *(values+j);
                    *(values+j) = *(values+j+1);
                    *(values+j+1) = swap;
                }
            }
        }
    }

    double* SensorArray:: GetRawPointer(){
        return values;
    }

    void SensorArray:: AddOffset(double offset, double* ptr){
        for(int i=0; i<size; i++){
            *(ptr+i) += offset;
        }
    }
    

    

    //constructor
     SensorArray::SensorArray(int size){
        this->size = size;
        values = new double[size];
        cout << "SensorArray of size " << size << " created." << endl;
        cout << "Address of size variable :" << &size << endl;
        cout << "Address stored in values pointer:" << values << endl;
     };

     SensorArray::~SensorArray(){
        cout << "[destructor] Releasing memeory at adress "<< values<< "\n" <<endl; 
        delete[] values;
     };



    }
