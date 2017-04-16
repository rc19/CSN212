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

void convexHull(vector<pair<int,int> > p){
	int n = p.size();
	vector<pair<int,int> > res;
	
	if(n < 3) return;
		
	int id = 0;
	for(int i = 1;i < n;i++){
		if(p[i].x < p[id].x) id = i;
	}
	
	int a = id, b;
	do{
		res.pb(p[a]);
		b = (a+1)%n;
		
		for(int i = 0;i < n;i++){
			if(order(p[a],p[i],p[b]) == 2) b = i;
		}
		
		a = b;
	}while(a != id);
	
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

void userInput(){
	int n,x,y;
	vector<pair<int,int> > p;
	ifstream in;
	in.open("100.txt");
	in>>n;
	for(int i = 0;i < n;i++){
		in>>x>>y;
		p.pb(mp(x,y));
	}
	
	//Special Case: All points on convex hull
	/*cout<<"Enter input size: ";
	cin>>n;
	for(int i = 1;i < n;i++){
		p.pb(mp(i,i));
	}
	p.pb(mp(0,1));
	*/
	
	convexHull(p);
}

int main(){
	clock_t startTime = clock();
	
	userInput();
	//testInput();
	
	double exeTime = double( clock() - startTime ) / (double)CLOCKS_PER_SEC;
	cout<<endl<<exeTime<<" seconds."<<endl;
	return 0;
}
