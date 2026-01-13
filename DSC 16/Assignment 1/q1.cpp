#include <bits/stdc++.h>
using namespace std;

double f(double x)
{
    return 27*pow(x,4)+162*pow(x,3)-180*pow(x,2)+62*x-7;
}

double df(double x)
{
    return 108*pow(x,3)+486*pow(x,2)-360*x+62;
}

int main()
{
    double p = 0.0;
    double alpha = 1.0/3.0;

    cout<<fixed<<setprecision(10);
    cout<<"n\tp_n\t\tError\n";

    for(int i=1;i<=10;i++)
    {
        p = p - f(p)/df(p);
        cout<<i<<"\t"<<p<<"\t"<<fabs(p-alpha)<<endl;
    }
}