//Orlando Lara A01631142
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

long fibonacci(long n){
  long pre2=0,pre1=1,fib;
  if(n==0 || n==1) return n;
  else{
    for(int i=0;i<n-1;i++){
      fib=pre1+pre2;
      pre2=pre1;
      pre1=fib;
    }
  }
  return fib;
}

int main(){
  long x,result;
  cout<<"What nth number of the fibonacci sequence do you want? ";
  cin>>x;    // this is the fib sequence 0,1,1,2,3,5,8,13,21,34,55,89............
  result=fibonacci(x);
  cout<<"The result is: "<<result<<endl;
}
