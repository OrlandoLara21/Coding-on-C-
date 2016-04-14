//Orlando Lara A01631142
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void line_print(int x){
  for(int i=0;i<x;i++) cout<<"T";
}

void triangles(int x){
  for(int i=1;i<=x;i++){  //specific number of times that the loop will be repeated
    line_print(i);
    cout<<endl;
  }
  for(int i=x;i>=1;i--){
    line_print(i);
    cout<<endl;
  }
}

int main(){
  int x;
  cout<<"Give me the maximum length of the triangle: ";
  cin>>x;
  triangles(x);
}
