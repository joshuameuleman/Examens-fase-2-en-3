#include <iostream>

using namespace std;

int main(){

    // matrix 3x3
    int matrix[3][3]= {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    // vector 3x1
    int vector[3]={2,1,3};

    int result[3]={0,0,0};

    //matrix-vector vermenigvuldiging

    for(int i=0; i<3; i++){
        for(int j = 0; j<3; j++){
            
            result[i] += matrix[i][j] * vector[j];
        }
    }

    //print result
    for(int i=0; i<3; i++){

        if(i==1){
            
            cout << "[" << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2] << "] [" << vector[i] << "] = [" << result[i] << "]" << endl;
        }
       else{

            cout << "[" << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2] << "] [" << vector[i] << "]   [" << result[i] << "]" << endl;

       } 
        
    }




    return 0;
}