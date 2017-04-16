#include<bits/stdc++.h>
# define PI 3.14159
using namespace std;

struct node
{
	int x; //To store the x-coordinate
	int y; //To store the y-coordinate
	double angle; //To store the angle
};

bool angle_sort(node one, node two)
{
	return (one.angle<two.angle)?1:0; //Comparing the angles of two nodes
}

bool rotation(node p,node q,node r)
{
    int val = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
 
    if (val > 0) //Checking if the rotation of points is clockwise or anti-clockwise
        return 1; 
    else
		return 0;
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
	
	node leftmost = coordinates[0];
    for (int i=1;i<n;i++)
    {
        if(leftmost.x>coordinates[i].x)
        	leftmost = coordinates[i];	//Finding the leftmost point in plane 
	}
	
	for(int i=0;i<n;i++)
	{
		if(coordinates[i].x!=leftmost.x || coordinates[i].y!=leftmost.y)
		{
			if(coordinates[i].y-leftmost.y!=0) //Checking the case for infinity slope
			{
				coordinates[i].angle = atan(double(coordinates[i].x-leftmost.x)/(-coordinates[i].y+leftmost.y))*180/PI; //Calculating the angle for each node
				
				if(coordinates[i].angle<0)
					coordinates[i].angle+=180;
			}
			else
				coordinates[i].angle = 90;
		}
	}
	
	sort(coordinates.begin(),coordinates.end(),angle_sort); //Sorting the coordinates according to the angle
	
	stack<node> points; //Maintaining two stacks simultaneously for iterations
	stack<node> prev;

	points.push(leftmost);
	points.push(coordinates[1]);
	
	prev.push(leftmost);
	for(int i=2;i<n;i++)
	{
		if(rotation(prev.top(),coordinates[i],points.top()))
		{
			prev.push(points.top());  //If they form a anti-clockwise pair, we will move to next point
			points.push(coordinates[i]);
		}
		
		else
		{
			while(!rotation(prev.top(),coordinates[i],points.top()))
			{
				points.pop();   //Pop from stack until we get anti-clockwise rotation
				prev.pop();
			}
			
			prev.push(points.top());
			points.push(coordinates[i]);
			
		}
	}
	
	while(!points.empty())
	{
		cout<<"("<<points.top().x<<","<<points.top().y<<") "; //Displaying final set of points forming convex hull
		points.pop();
	}
	
}
