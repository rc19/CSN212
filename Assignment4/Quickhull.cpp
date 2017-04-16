#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define x first
#define y second

using namespace std;

int order(pair<int,int> a, pair<int,int> b, pair<int,int> c){
	int det = (b.x-a.x)*(c.y-b.y) - (c.x-b.x)*(b.y-a.y);
	if(det == 0) return 0;           //points are collinear
	if(det < 0)  return 1;           //a,b,c are clockwise 
	return 2;						 //a,b,c are anti-clockwise
}

double getDist(pair<int, int> p0, pair<int, int> a, pair<int, int> b){
	double m = (double)((b.y-a.y)*1.0)/(b.x-a.x);
	double c = a.y-m*a.x;			//line eqn: mx-y+c = 0
	double dist = (abs(m*p0.x-p0.y+c))/sqrt(m*m+1);
	return dist;
}

void qhull(vector<pair<int,int> > p, pair<int, int> a, pair<int, int> b, vector<pair<int, int> >&res){
	int n = p.size();
	if(n == 0) return;
	
	double dist = 0;
	int id;
	for(int i = 0;i < n;i++){
		if(dist < getDist(p[i],a,b)){
			id = i;
			dist = getDist(p[i],a,b);
		}
	}
	res.pb(p[id]);
	
	vector<pair<int, int> >p1, p2;
	for(int i = 0;i < n;i++){
		if(order(a, p[i], p[id]) == 2)  p1.pb(p[i]);
		else if(order(p[id], p[i], b) == 2) p2.pb(p[i]);
	}
	qhull(p1,a,p[id],res);
	qhull(p2,p[id],b,res);
}

void convexHull(vector<pair<int,int> > p){
	int n = p.size();
	vector<pair<int, int> > res, p1, p2;
	
	int id1 = 0, id2 = 0;
	for(int i = 1;i < n;i++){
		if(p[i].x < p[id1].x) id1 = i;
		else if(p[i].x > p[id2].x) id2 = i;
	}
	res.pb(p[id1]); res.pb(p[id2]);
	
	int f;
	for(int i = 0;i < n;i++){
		f = order(p[id1], p[i], p[id2]);
		if(f == 2)  p1.pb(p[i]);
		else if(f == 1) p2.pb(p[i]);
	}
	
	qhull(p1,p[id1],p[id2],res);
	qhull(p2,p[id2],p[id1],res);
	
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
	p.pb(mp(1,2));
	p.pb(mp(3,1));
	p.pb(mp(0,0));
	p.pb(mp(3,3));
	p.pb(mp(4,4));
	
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
