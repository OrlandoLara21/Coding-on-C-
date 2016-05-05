#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;
using std::abs;
const float pi = acos(-1);
struct parts{
  float x,y,t,theta,alpha,f,k,o;
};

float radian(float x){
  x=x*pi/180;
  return x;
}
float degree(float x){
  x=x*180/pi;
  return x;
}
float calculate_moment(parts distance,parts force){
  float moment;
  moment=(distance.x*force.f*cos(radian(force.theta))) - (distance.y*force.f*cos(radian(force.alpha)));
  return moment;
}
float calculate_triangle(float sigma, parts spring2_boom, parts arm_extra){
  parts spring2;
  arm_extra.y=arm_extra.t*sin(radian(180-sigma)); //0.866
  arm_extra.x=arm_extra.t*cos(radian(180-sigma)); //0.5
  spring2.x=spring2_boom.t-arm_extra.x;
  spring2.y=arm_extra.y;
  spring2.t=sqrt(spring2.x*spring2.x + spring2.y*spring2.y);
  return spring2.t;
}

bool test_run(parts spring1,parts boom,parts arm,parts syringe,parts syringe2,parts boom_spring,parts spring2_boom,parts spring2,float x1,float x2,float xt,float y,float mweight,float mweight2,float mspring,float mspring2,float msyringe,float msyringe2,float arm_syr,float sigma,float gamma,parts arm_extra,int boom_syr,float weight, float force, float k, float rest,float rest2, float k2,float altitude){
  bool condition=false;
  int indicator=0;
  spring2.o=spring2.t;
  for(syringe.t=13.5;syringe.t<=17.1;syringe.t+=0.1){
    for(syringe2.t=13.5;syringe2.t<=17.1;syringe2.t+=0.1){
      x1=(syringe.t*syringe.t-boom_syr*boom_syr-xt*xt)/(-2*xt);
      x2=xt-x1;
      y=sqrt(boom_syr*boom_syr-x1*x1);
      boom.alpha=degree(atan(y/x1));
      syringe.theta=90-degree(atan(y/x2));
      boom_spring.x=boom_spring.t*cos(radian(boom.alpha));
      boom_spring.y=boom_spring.t*sin(radian(boom.alpha));
      //We have defined the changed occured in the base
      spring1.alpha=90+boom.alpha;
      spring1.theta=boom.alpha;
      spring1.x=boom_spring.x+4.5;
      spring1.t=spring1.x/(-cos(radian(spring1.alpha)));
      spring1.y=sqrt(spring1.t*spring1.t-spring1.x*spring1.x);
      spring1.f=spring1.k*(spring1.t-rest);
      //we have defined the changed occured in spring1
      if((syringe2.t/2)>=arm_syr){
        indicator=5;
        break; //if it is bigger it could break the connection
      }
      gamma=degree(acos((syringe2.t/2)/arm_syr));
      sigma=180-(gamma*2);
      arm.alpha=180-boom.alpha-sigma;
      arm.theta=90+arm.alpha;
      //we have defined the change occured in the the second syringe parts
      boom.x=boom.t*cos(radian(boom.alpha));
      arm.x=arm.t*cos(radian(arm.alpha));
      //this defined the distances of the boom and arm to calculate moments for the weight
      arm_extra.alpha=180-arm.alpha;
      arm_extra.theta=90-arm.alpha;
      arm_extra.x=arm_extra.t*cos(radian(arm_extra.alpha));
      arm_extra.y=arm_extra.t*cos(radian(arm_extra.theta));
      //This defined the change occured in the distance to the second spring2_boom
      spring2.alpha=arm.alpha+90;  //fix this
      spring2.theta=180-arm.alpha;
      spring2.t=calculate_triangle(sigma,spring2_boom,arm_extra);  //make a calculate triangle function
      spring2.f=spring2.k*(spring2.t-rest2);
      if(spring2.t<rest2){
        indicator=5;
        break;
      }
      //this defined the change occured in spring2
      mweight=(boom.x+arm.x)*weight;
      mweight2=arm.x*weight;
      msyringe=xt*force*cos(radian(syringe.theta));
      msyringe2=arm_syr*force*sin(radian(gamma));
      mspring=calculate_moment(boom_spring,spring1);
      mspring2=calculate_moment(arm_extra,spring2);
      //this defined the change occured in the moments
      if((msyringe+mspring)<mweight && (msyringe2+mspring2)<mweight2){
        indicator=5;
        break;
      }
    }
    if(indicator==5) break;
  }
  if(indicator!=5){
    cout<<"*****************************************************************"<<endl;
    cout<<"boom_syr:"<<boom_syr;
    cout<<"\tboom.alpha:"<<boom.alpha;
    cout<<"\tboom_spring.t:"<<boom_spring.t;
    cout<<"\tboom.t:"<<boom.t;
    cout<<"\tsyringe.theta:"<<syringe.theta;
    cout<<"\txt:"<<xt;
    cout<<"\tarm.t:"<<arm.t;
    cout<<"\tspring1.t:"<<spring1.t;
    cout<<"\tspring1.f:"<<spring1.f<<endl;
    cout<<"mspring:"<<mspring;
    cout<<"\tmsyringe:"<<msyringe;
    cout<<"\tmweight:"<<mweight;
    cout<<"\tspring2_boom.t:"<<spring2_boom.t;
    cout<<"\tspring2.t:"<<spring2.t;
    cout<<"\tspring2.f:"<<spring2.f;
    cout<<"\tmspring2:"<<mspring2;
    cout<<"\tmsyringe2:"<<msyringe2<<endl;
    cout<<"mweight2:"<<mweight2;
    cout<<"\tarm_extra.t: "<<arm_extra.t;
    cout<<"\taltitude: "<<altitude;
    cout<<"\tsigma: "<<sigma<<endl;
    condition=true;
  }
  return condition;
}


void run_simulation(float weight, float force, float k, float rest,float rest2, float k2){
  parts spring1,boom,arm,syringe,syringe2,boom_spring,spring2_boom,spring2,arm_extra;
  float x1,x2,xt,y,mweight,mweight2,mspring,mspring2,msyringe,msyringe2,arm_syr,sigma,gamma,altitude;
  int boom_syr;
  for(boom_syr=6;boom_syr<=15;boom_syr++){
    for(boom.alpha=15;boom.alpha<=30;boom.alpha++){
      for(boom_spring.t=6;boom_spring.t<=15;boom_spring.t++){
        for(arm_extra.t=3;arm_extra.t<=18;arm_extra.t++){
          boom_spring.x=boom_spring.t*cos(radian(boom.alpha));
          boom_spring.y=boom_spring.t*sin(radian(boom.alpha));
          syringe.t=13.5;
          syringe2.t=13.5;
          x1=boom_syr*cos(radian(boom.alpha));
          y=boom_syr*sin(radian(boom.alpha));
          x2=sqrt(syringe.t*syringe.t - y*y);
          xt=x1+x2;
          //this defined the base
          syringe.theta=90-degree(asin(y/syringe.t));
          spring1.alpha=90+boom.alpha;
          spring1.theta=boom.alpha;
          spring1.x=boom_spring.t*cos(radian(boom.alpha));
          spring1.t=spring1.x/(-cos(radian(spring1.alpha)));
          spring1.y=sqrt(spring1.t*spring1.t - spring1.x*spring1.x);
          spring1.k=k/100;
          spring1.f=spring1.k*(spring1.t-rest);
          altitude=boom_spring.y+spring1.y;
          if(spring1.t>26) break;
          //this defined the angles and size of the first spring
          arm.alpha=45;
          arm.theta=90+arm.alpha;
          sigma= 180-boom.alpha-45;  //sigma is the angle between the boom and the arm
          gamma=(180-sigma)/2;
          arm_syr= (syringe2.t/2)/cos(radian(gamma));
          //this defined the second syringe distances
          if(boom_spring.t>=boom_syr) boom.t=boom_spring.t+3+arm_syr;
          else boom.t=boom_syr+3+arm_syr;
          boom.x=boom.t*cos(radian(boom.alpha));
          boom.y=boom.t*sin(radian(boom.alpha));
          arm.t=boom.y/sin(radian(arm.theta));
          arm.x=arm.t*cos(radian(arm.alpha));
          if(arm.t<arm_syr) break;
          //this defined the length of the arm and put a conditional in case the lengths don't make sense
          arm_extra.alpha=180-arm.alpha;
          arm_extra.theta=90-arm.alpha;
          arm_extra.x=arm_extra.t*cos(radian(arm_extra.alpha));
          arm_extra.y=arm_extra.t*cos(radian(arm_extra.theta));
          //this is the postion at which the second spring will be placed on the boom
          spring2.alpha=arm.alpha+90;
          spring2.theta=180-arm.alpha;
          spring2.t=arm_extra.t*tan(radian(180-sigma));
          spring2.x=spring2.t*cos(radian(spring2.alpha));
          spring2.y=sqrt(spring2.t*spring2.t - spring2.x*spring2.x);
          spring2.k=k2/100;
          spring2.f=spring2.k*(spring2.t-rest2);
          spring2_boom.t=arm_extra.t/cos(radian(180-sigma));
          if(spring2.t>26) break;
          if(spring2_boom.t>boom.t) break;
          if((abs(boom_syr-boom_spring.t))<3) break;
          //this defined the size and angles of the second spring
          mweight=(boom.x+arm.x)*weight;
          mweight2=arm.x*weight;
          msyringe=xt*force*cos(radian(syringe.theta));
          msyringe2=arm_syr*force*sin(radian(gamma));
          mspring=calculate_moment(boom_spring,spring1);
          mspring2=calculate_moment(arm_extra,spring2);
          //this defined the moments
          if((mspring+msyringe)>=mweight && (mspring2+msyringe2)>=mweight2)
          if(test_run(spring1,boom,arm,syringe,syringe2,boom_spring,spring2_boom,spring2,x1,x2,xt,y,mweight,mweight2,mspring,mspring2,msyringe,msyringe2,arm_syr,sigma,gamma,arm_extra,boom_syr,weight,force,k,rest,rest2,k2,altitude)){
            cout<<"*"<<endl;
            cout<<"boom_syr:"<<boom_syr;
            cout<<"\tboom.alpha:"<<boom.alpha;
            cout<<"\tboom_spring.t:"<<boom_spring.t;
            cout<<"\tboom.t:"<<boom.t;
            cout<<"\tsyringe.theta:"<<syringe.theta;
            cout<<"\txt:"<<xt;
            cout<<"\tarm.t:"<<arm.t;
            cout<<"\tspring1.t:"<<spring1.t;
            cout<<"\tspring1.f:"<<spring1.f<<endl;
            cout<<"mspring:"<<mspring;
            cout<<"\tmsyringe:"<<msyringe;
            cout<<"\tmweight:"<<mweight;
            cout<<"\tspring2_boom.t:"<<spring2_boom.t;
            cout<<"\tspring2.t:"<<spring2.t;
            cout<<"\tspring2.f:"<<spring2.f;
            cout<<"\tmspring2:"<<mspring2;
            cout<<"\tmsyringe2:"<<msyringe2<<endl;
            cout<<"mweight2:"<<mweight2;
            cout<<"\tarm_extra.t: "<<arm_extra.t;
            cout<<"\taltitude: "<<altitude;
            cout<<"\tarm_syr: "<<arm_syr;
            cout<<"\tsigma: "<<sigma<<endl;
          }
        }
      }
    }
  }
}

int main(){
  float weight, force, k, rest,rest2,k2;
  cout<<"This program will give you the dimensions you need"<<endl;
  cout<<"What is the weight: "; cin>>weight;
  cout<<"What is the force in the syringe: "; cin>>force;
  cout<<"What is the k: "; cin>>k;
  cout<<"What is the rest position: "; cin>>rest;
  cout<<"What is the k2: "; cin>>k2;
  cout<<"What is the rest2 position: "; cin>>rest2;
  run_simulation(weight,force,k,rest,rest2,k2);
}
