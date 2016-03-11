#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int find_threes(vector<int> & v,int size){
  int sum=0;
  for(int n=0;n<size;n++){
    if((v[n]%3)==0)
    sum+=v[n];
  }
  return sum;
}

int main(){
  vector<int> v;
  int sum=0;
  int x;
  cout<<"with any series of numbers that you give me, I will find those\nthat can be evenly divided by three and add them up"<<endl;
  cout<<"Enter a series of numbers and when you are done, enter a 0"<<endl;
  while(cin>>x,x!=0)
  v.push_back(x);
  sum=find_threes(v,v.size());
  cout<<"The sum is equal to: "<<sum<<endl;
}
