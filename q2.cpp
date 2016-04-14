//orlando Lara A01631142
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

long superpower(long a, long b){
  long r=1;
  for(int i=0;i<b;i++){     //a*a*a
    r*=a;  //a=2  b=1 ; loop runs one time, r= 1*2=2
  }
  return r;
}

int main(){
  long  x,y,result;
  cout<<"What is the base number? ";
  cin>>x;
  cout<<"What is the exponent number? ";
  cin>>y;
  result=superpower(x,y);
  cout<<"The result is: "<<result<<endl;
}
