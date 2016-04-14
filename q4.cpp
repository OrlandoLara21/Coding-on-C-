//Orlando Lara A01631142
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

string case_check(string x){
  for(int i=0;i<x.size();i++){  //Racecar   x[2]=c
    if(x[i]>64 && x[i]<91) x[i]+=32;
  }
  return x;  //racecar
}

bool isPalindrome(string x){
  string y,flipy;
  y=case_check(x);
  flipy=string(y.rbegin(),y.rend());
  if(y==flipy) return true;
  else return false;
}

int main(){
  string x;
  bool what;
  cout<<"Write a string of characters: ";
  getline(cin,x);
  what=isPalindrome(x);
  if(what) cout<<"This is a palindrome"<<endl;  //if(true)
  else cout<<"FAIL"<<endl;
}
