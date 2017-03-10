#include<bits/stdc++.h>

using namespace std;

bool rest_t(int a,int b,vector< vector<int> >not_allow_t,int n)
{
	for(int i=0;i<n;i++)
	{
		if(not_allow_t[i][0]==a && not_allow_t[i][1]==b)
		{
			return 1;
		}
	}
	return 0;
}

bool rest_r(int a,int b,vector< vector<int> >not_allow_r,int n)
{
	for(int i=0;i<n;i++)
	{
		if(not_allow_r[i][0]==a && not_allow_r[i][1]==b)
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	int width,height;
	cin>>width>>height;
	
	int n;
	cin>>n;
	string bad[n],s1,s2,s3,s4;
	
	int length[n];
	for(int i=0;i<n;i++)
	{
		cin>>s1>>s2>>s3>>s4;  //Taking input of bad elements as concatenation of four strings
		bad[i]=s1+" "+s2+" "+s3+" "+s4;
		length[i]=s1.length()+s2.length()+s3.length()+s4.length()+3;
	}
	
	for(int i=0;i<n;i++)
		cout<<bad[i]<<endl;
				
	vector< vector<int> >not_allow_r(n,vector< int >( 2 ) ); //right dir.
	vector< vector<int> >not_allow_t(n,vector< int >( 2 ) );   //top dir.
	for(int i=0;i<n;i++)
	{
		not_allow_t[i][0]=-1;
		not_allow_t[i][1]=-1;
	}
	for(int i=0;i<n;i++)
	{
		not_allow_r[i][0]=-1;
		not_allow_r[i][1]=-1;
	}
	
	int nar=0,nat=0;
	
	for(int i=0;i<n;i++)
	{
		bool prev=1;
		int num=1,a,b,c,d;
		for(int j=0;j<length[i];j++)
		{
			if(bad[i][j]!=' '&&prev==1)
			{
				if(num==1)
					a=(int)bad[i][j]-48;
				else if(num==2)
					b=(int)bad[i][j]-48;
				else if(num==3)
					c=(int)bad[i][j]-48;
				else
					d=(int)bad[i][j]-48;
				
				prev=0;
			}
			else if(bad[i][j]!=' '&&prev==0)
			{
				if(num==1)
					a=10*a+(int)bad[i][j]-48;
				else if(num==2)
					b=10*b+(int)bad[i][j]-48;
				else if(num==3)
					c=10*c+(int)bad[i][j]-48;
				else
					d=10*d+(int)bad[i][j]-48;
			}
			else
			{
				num++;
				prev=1;
			}
		}
		
		if(c==a+1 && b==d)
		{
			not_allow_r[nar][0]=a;
			not_allow_r[nar][1]=b;
			nar++;
		}
		if(c==a-1 && b==d)
		{
			not_allow_r[nar][0]=c;
			not_allow_r[nar][1]=d;
			nar++;
		}
		if(c==a && b==d+1)
		{
			not_allow_t[nat][0]=c;
			not_allow_t[nat][1]=d;
			nat++;
		}
		if(c==a && b==d-1)
		{
			not_allow_t[nar][0]=a;
			not_allow_t[nar][1]=b;
			nat++;
		}
	}
	
	long long ar[101][101];
	ar[0][0]=1;
	for(int i=0;i<=width;i++)
	{
		for(int j=0;j<=height;j++)
		{
			if(i>0 && !rest_r(i-1,j,not_allow_r,n))
				ar[i][j]+=ar[i-1][j];
			if(j>0 && !rest_t(i,j-1,not_allow_t,n))
				ar[i][j]+=ar[i][j-1];
		}
	}
	cout<<ar[width][height]<<endl;
}
