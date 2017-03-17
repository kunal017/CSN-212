#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--)
	{
	    //Some Inputs and outputs computed are given below.
	    int v,e;
	    cin>>v>>e;
	    int ar[e][2];
	    bool bo = false; //variable to detect if negative-weight cycle exists
	    int w[e]; //w[i] is the weight of each edge directed from ar[i][0] -> ar[i][1]
	    int d[v+1]={0}; //d[i] is the minimum distance from vertex s
	    d[1] = 0; //Making distance for 1st vertex as zero
	    
	    for(int i=0;i<e;i++)
	        cin>>ar[i][0]>>ar[i][1]>>w[i];
	    for(int i=2;i<=v;i++) //Initialization
	        d[i] = 2100000000; //Assuming weights are less than 47483647
	   
	    for(int i=1;i<v;i++)
	    {
	        for(int j=0;j<e;j++)
	        {
	            if(d[ar[j][1]]>d[ar[j][0]]+w[j]) //Relaxation Step
	                d[ar[j][1]]=d[ar[j][0]]+w[j];
	        }
	    }
	    
	    for(int i=0;i<e;i++)
	    {
	        if(d[ar[i][1]]>d[ar[i][0]]+w[i]) //Checking for negative-weight cycle
	        {
	            bo = true;
	            break;
	        }
	    }
	    
	    if(bo==true)
	        cout<<"Negative-weight cycle exists"<<endl;
	    else
	    {
	        for(int i=1;i<=v;i++)
	            cout<<d[i]<<" ";
	        cout<<""<<endl;
	    }
	}
}
/*Inputs
4   ->Test cases
5 9
1 2 10
1 3 3
2 3 1
2 4 2
3 2 4
3 4 8
3 5 2
4 5 7
5 4 9

6 8
1 2 10
1 6 8
2 4 2
3 2 1
4 3 -12
5 4 -1
5 2 -4
6 5 1

5 8
1 2 -1
1 3 4
2 3 3
2 4 2
2 5 2
4 2 1
4 3 5
5 4 -3
 
6 8
1 2 10
1 6 8
2 4 2
3 2 1
4 3 -2
5 4 -1
5 2 -4
6 5 1

Outputs

0 7 3 9 5 
Negative-weight cycle exists
0 -1 2 -2 1 
0 5 5 7 9 8

*/
