#include<bits/stdc++.h>
using namespace std;
 
int findIndex(vector<int> &v, int lef, int rig, int key) 
{
    while(rig-lef>1) 
    {
        int mid = lef + (rig-lef)/2;
        if (v[mid]>=key)
            rig = mid;
        else
            lef = mid;
    }
 
    return rig;
}
 
int lucky_draw(int ar[], int n)
{
	vector<int> dummy(10005);
	dummy[0]=ar[0];
	int length=1;
	for(int i=0;i<n;i++)
	{
		if(ar[i]<dummy[0])
		{
			dummy[0]=ar[i];
		}
		else if(ar[i]>dummy[length-1])
		{
        	dummy[length]=ar[i];
        	length++;
		}
        else
        {
        	dummy[findIndex(dummy,-1,length-1,ar[i])]=ar[i];
		}   
	}
	
	return length;
}
 
int main()
{
	int t;
	cin>>t;
	int ar[10005*2];
	
	while(t--)
	{
		int n,ans=0;
		cin>>n;
		for(int i=0;i<n;i++)
		{
			cin>>ar[i];
			ar[n+i]=ar[i];
		}
		for(int i=0;i<n;i++)
		{
			ans=max(ans, lucky_draw(ar+i,n));
		}
		
		cout<<ans<<endl;
	}
}
