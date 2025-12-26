// Demo les 1 - The basics
// We start off with the hello world example
// Compile with: g++ main.cpp -o basic.exe
// Execute with: ./basic

#include <iostream> //zorg voor input en output
    // # = pre-processor directive
    // Runs before compiler
    // Includes the whole iostream library file

using namespace std; //you don't have to type std:: before every cout or endl
    // Open the standard namespace

int main() {
  // Entrypoint for the application

  cout << "Hello world!" << endl;
    // cout = console out
    // endl = end line + flush

    //----------------
    //Variables
  int age=23;

  cout<<"my age is "<<age<<endl;

  cout<<"number of bytes for int:"<<sizeof(age)<<endl;

  long long int veryLongInt=123;
  
  cout<<"Size of long long int:"<<sizeof(veryLongInt)<<endl;

  cout<<"a very long number:"<<1'323'223 << endl;

  cout<<"A Special floating point:"<<34.234'323<<endl;

  cout<<"Zero dot one:"<< 0.1<<endl;

  //characters
  char start=56;
  cout<<"character "<<start<<endl;
  cout<< "Char Start :"<<(int)start<<endl;
  char stop=0x50;
  cout<<"character stop;"<<stop<<endl;
  char binary=0b1001'0101;
  char oct=060;
  char character= 'a';

  //floating point
  double floating=3.14159;
  float smallerFloat=3.14f;

  //Boolean
  bool theTruth=true;
  bool test=123;

  //initialization
  int sum;
  cout<<"sum before init:"<<sum<<endl;
  int total=0;

  //constants
  const int NUMBER_OF_STUDENTS=30;
  //PREPROCESSOR DEFINE (AVOID THIS!)
  #define MAX_STUDENTS 50

  //----------------
  //Operators

  //arithmetic operators
  double value=33/2;
  cout<<"value:"<<value<<endl;

  double floatingValue=33.0/2;
  floatingValue=33.0/2.0;
  floatingValue=((double)33)/2;

  //Increments
  int c=3;
  c++;
  cout<<"c after c++:"<<c<<endl;
  int z= c++;
  cout<<"c after c++:"<<c<<endl;
  cout<<"z after c++:"<<z<<endl;
  int w= ++c;
  cout<<"c after c++:"<<c<<endl;
  cout<<"w after c++:"<<w<<endl;

  //logical operators
  bool a =true;
  bool b = false;
  if(a&&b){
    cout<<"both true"<<endl;
  }
  else{
    cout<<"at least one false"<<endl;
  }
  int i = 0;
  if(a||(++i)){
    cout<<"Either is true"<<endl;
    cout<<"i="<<i<<endl;
  }

  //ternary operator
  cout<<(i==0?"yoepile":"ahh")<<endl;
  
  //binary
  char A=0b0000'10101;
  char B=0b0000'1111;
  char C=0b0000'0001;
  unsigned char D= A&B;
  unsigned char E= A|B;
  unsigned char F= C << 2;
  unsigned char G=A^B;
  cout<<"D:A&B:"<<(int)D<<endl;
  cout<<"E:A|B:"<<(int)E<<endl;
  cout<<"F:C<<2:"<<(int)F<<endl;
  cout<<"G:A^B:"<<(int)G<<endl;

  //Unary
  int one =-1;
  unsigned char H=~A;
  bool two=!false;


  //input stream

  cout<<"Please enter two numbers:";
  int numberA;
  int numberB;
  cin>>numberA>>numberB;
  cout<<"sum is:"<<(numberA+numberB)<<endl;

  int hv=0;
  cout<<"PLease enter a hex value:";
  cin >> hex>>hv;
  cout <<"The decimal value is:"<<dec<<hv<<endl;
  










  return 0;
    // status code end of program
    // different from 0 = FAIL
}
