#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define x first
#define y second

using namespace std;
pair<int,int> p0;

int order(pair<int,int> a, pair<int,int> b, pair<int,int> c){
	int det = (b.x-a.x)*(c.y-b.y) - (c.x-b.x)*(b.y-a.y);
	if(det == 0) return 0;           //points are collinear
	if(det < 0)  return 1;           //a,b,c are clockwise 
	return 2;						 //a,b,c are anti-clockwise
}

bool comp(pair<int,int> a, pair<int,int> b){
	int f = order(p0,a,b);
	
	if(f == 0)  return (((p0.x - a.x)*(p0.x - a.x)+(p0.y - a.y)*(p0.y - a.y)) <= ((p0.x - b.x)*(p0.x - b.x)+(p0.y - b.y)*(p0.y - b.y)));
	
	return (f == 1)?0:1;
}

void convexHull(vector<pair<int,int> > p){
	int n = p.size();
	vector<pair<int,int> > res;
	
	//find the bottommost point
	int id = 0;
	for(int i = 1;i < n;i++){
		if(p[i].y < p[id].y) id = i;
		else if(p[i].y == p[id].y && p[i].x < p[id].x) id = i;
	}
	swap(p[0],p[id]);
	p0 = p[0];
	
	sort(p.begin()+1,p.end(),comp);
	for(int i = 0; i < p.size();i++)
		cout<<"("<<p[i].x<<","<<p[i].y<<")\t";
	//Result
	cout<<"Points on the convex hull in anti-clockwise order are:\n";
	for(int i = 0; i < res.size();i++)
		cout<<"("<<res[i].x<<","<<res[i].y<<")\t";
}

void testInput(){
	vector<pair<int,int> > p;
	
	p.pb(mp(1,1));
	p.pb(mp(2,2));
	p.pb(mp(0,3));
	p.pb(mp(2,1));
	p.pb(mp(3,0));
	p.pb(mp(0,0));
	p.pb(mp(3,3));
	
	convexHull(p);
}

int main(){
	clock_t startTime = clock();
	
	//userInput();
	testInput();
	
	double exeTime = double( clock() - startTime ) / (double)CLOCKS_PER_SEC;
	cout<<endl<<exeTime<<" seconds."<<endl;
	return 0;
}