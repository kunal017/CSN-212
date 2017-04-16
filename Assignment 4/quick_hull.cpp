#include<bits/stdc++.h>
using namespace std;

struct node
{
	int x; //To store the x-coordinate
	int y; //To store the y-coordinate
};

bool clock(node p, node q, node r)
{
    int val = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
 	
	 if (val < 0) //Checking if point lies on left side or the right side of line
        return 1;
    else
		return 0;
}

void display_vec(vector<node> a)
{
	for(int i=0;i<a.size();i++)
	{
		cout<<"("<<a[i].x<<","<<a[i].y<<")  "; //Displaying all the coordinates of vector
	}
	cout<<""""<<endl;
}

vector<node> finding_pts(node A, node B, vector<node> points)
{
	vector<node> random;
	
	for(int i=0;i<points.size();i++)
	{
		if(clock(A,B,points[i]))
			random.push_back(points[i]); //Finding all points lying on left side of line joining A and B
	}
	
	return random;
}

void find_hull(vector<node> points, node A, node B)
{
	if(points.size()==0) //Checking if no point lies in other region
		return;
		
	double dist = 0,k;
	int ans;
	
	for(int i=0;i<points.size();i++)
	{
		int x = points[i].x;
		int y = points[i].y;
		
		k = abs((B.y-A.y)*x-(B.x-A.x)*y+B.x*A.y-B.y*A.x)/sqrt(pow(B.y-A.y,2)+pow(B.x-A.x,2)); //Finding the perpendicular distance from line
		
		if(k>dist)
		{
			dist = k;
			ans = i; //Storing the index of node with maximum distance from the line
		}
	}
	
	cout<<"Coordinates of node are ("<<points[ans].x<<","<<points[ans].y<<") "<<endl;
	
	vector<node> points1 = finding_pts(A,points[ans],points);
	vector<node> points2 = finding_pts(points[ans],B,points);
	
	//Finding points for two different regions and then finding their convex hull
	
	find_hull(points1,A,points[ans]);
	find_hull(points2,points[ans],B);	
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
	
	cout<<""<<endl;
	
	node leftmost = coordinates[0];
    node rightmost = coordinates[0];
    
	for(int i=1;i<n;i++)
    {
        if(leftmost.x>coordinates[i].x)  
        	leftmost=coordinates[i];   //Finding the leftmost point in the plane
        if(rightmost.x<coordinates[i].x)        	
			rightmost=coordinates[i];   //Finding the rightmost point in the plane
	}
	
	cout<<"Coordinates of node are ("<<leftmost.x<<","<<leftmost.y<<") "<<endl; //Finding hull for upper half
	vector<node> leftpoints = finding_pts(leftmost,rightmost,coordinates);
	
	find_hull(leftpoints,leftmost,rightmost);
	
	cout<<"Coordinates of node are ("<<rightmost.x<<","<<rightmost.y<<") "<<endl; //Finding hull for lower half
	vector<node> rightpoints = finding_pts(rightmost,leftmost,coordinates);
	
	find_hull(rightpoints,rightmost,leftmost);	
}
