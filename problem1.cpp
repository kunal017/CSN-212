#include<bits/stdc++.h>
using namespace std;

int longestZigZag(int* A, int n)
{
  	int ar[n][2];
  	for(int i=0;i<n;i++)
  	{
  		for(int j=0;j<2;j++)
  		{
			ar[i][j] = 0;
		}	
	}
  	
	ar[0][0] = 1;
  	ar[0][1] = 1;
  
  	int ans = 1;
  
  	for(int i=1;i<n;i++)
  	{
    	for(int j=i-1;j>=0;j--)
		{
      		if(A[j]<A[i]) 
	  			ar[i][0] = max(ar[j][1]+1, ar[i][0]);
      		if(A[j]>A[i]) 
			  	ar[i][1] = max(ar[j][0]+1, ar[i][1]);
    	}
    	ans = max(ans, max(ar[i][0],ar[i][1]));
  	}
  	
  	return ans;
}
 
int main()
{
	int n;
	cin>>n;
	int A[n]; //Input sequence
	for(int i=0;i<n;i++)
	{
		cin>>A[i];
	}	
		
	cout<<longestZigZag(A,n)<<endl;
}
