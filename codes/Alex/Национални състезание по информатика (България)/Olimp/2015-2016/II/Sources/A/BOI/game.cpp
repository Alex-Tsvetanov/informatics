#include<iostream>
#include<cmath>

using namespace std;

const double PI = 3.14159;

int main()
{
	int Z, Q;
	long long p[10000];
	double cx[10000], cy[10000], cc[10000], tx[10], ty[10];
	short M;
	cin>>Z>>M>>Q;
	for(int i=0; i<Z;i++)
	{	
		cin>>cx[i];
		cin>>cy[i];
		cin>>cc[i];
	}
	for(int j=0; j<M;j++)
	{	
		cin>>tx[j];
		cin>>ty[j];
	}
	for(int k=0; k<Q; k++)
	{	
		cin>>p[k];
	}


	int s=0;
	for(int j=0; j<M;j++)
	{	
		double ind=1;
		double dx, dy;
		for(int k=0; k<Q; k++)
		{
				double r = p[k]*ind;
				int br=0;
		for(int i=0; i<Z;i++) 
	{	
		
			double radius = cc[i];
			int flag=1;
			for (double angle=0; angle<=2*PI; angle+=0.001)
		{
		dx = cx[i] + radius*cos( angle );
		dy = cy[i] + radius*sin( angle );
		if(sqrt(pow(fabs(dx-tx[j]),2)+pow(fabs(dy-ty[j]),2))>r)
		{
			flag=0;
			break;
		}
		}
			if(flag==1)
				br++;
	}
	
		s+=br;
		if(br%2==0)
			ind=2;
		else
			ind=1;
		}
	}
		
		
		cout<<s<<endl;

return 0;
}

