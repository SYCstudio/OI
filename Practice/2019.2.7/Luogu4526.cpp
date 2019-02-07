#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

const double eps=1e-8;

double A;

double Calc(double x);
double Inte(double l,double r);
double Simpson(double l,double r);

int main(){
    scanf("%lf",&A);
    if (A<0){
        printf("orz\n");return 0;
    }
    printf("%.5lf\n",Simpson(eps,15));
    return 0;
}
double Calc(double x){
    //cout<<"Calc:"<<x<<" "<<pow(x,A/x-x)<<endl;
    return pow(x,A/x-x);
}
double Inte(double l,double r){
    return (r-l)*(Calc(l)+Calc(r)+4*Calc((l+r)/2))/6;
}
double Simpson(double l,double r){
    double mid=(l+r)/2,k=Inte(l,r),kl=Inte(l,mid),kr=Inte(mid,r);
    if (fabs(kl+kr-k)<eps) return kl+kr;
    return Simpson(l,mid)+Simpson(mid,r);
}