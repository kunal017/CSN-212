#include <bits/stdc++.h>
using namespace std;
 
struct node
{
	int x; //To store the x-coordinate
	int y; //To store the y-coordinate
};

int orientation(node p, node q, node r)
{
    int val = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
 
    if (val==0)
        return 0; // Checking if points are collinear
        
    return (val>0) ? 1 : 2; // Checking for clockwise or counterclock wise rotation
}
 
void convex_Hull(vector<node> points, int n)
{
   	if(n<3)
        return; //Convex Hull should not be of less than 3 points
 
    int ar[n];
    for(int i=0;i<n;i++)
    	ar[i] = -1; //Initializing each value to -1
 
    int left = 0;
    for(int i=1;i<n;i++)
    {
        if(points[i].x<points[left].x) // Finding the leftmost point
            left = i;
 	}
 	
    int p=left,temp;
    
	do
    {
        temp = (p+1) % n;
        for (int i = 0; i < n; i++)
            if (orientation(points[p], points[i], points[temp])==2) //Checking for counterclockwise rotation
                temp = i;
 
        ar[p]=temp;
        p=temp;
    }
    while(p!=left); //Until it reaches the starting point
 
    for(int i=0;i<n;i++)
    {
        if (ar[i] != -1)
            cout<<"("<<points[i].x<<", "<<points[i].y<<")\n"; //Printing the convex hull made by set of points
    }
}
 
int main()
{
	int n;
	cin>>n;
	vector<node> coordinates(n);
	for(int i=0;i<n;i++)
	{
		cout<<"Enter x coordinate"<<i+1<<": ";
		cin>>coordinates[i].x;
		cout<<"Enter y coordinate"<<i+1<<": ";
		cin>>coordinates[i].y;
	}
    convex_Hull(coordinates,n); //Calling the function for convex hull
}
