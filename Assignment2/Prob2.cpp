/* Link to the problem:
https://community.topcoder.com/stat?c=problem_statement&pm=1889


"edge" matrix description
0 = no obstruction
1 = can't come from left
2 = can't come from down
3 = unreachable

Important Note: Elements of the string "bad" can only be separated by comma whereas
	            the values a,b,c,d of each element are separated by a single space.
	            Therefore, keep caution about the format of the input for getting
	            the correct result.
*/



#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll numWays(int w, int h, string bad){
	vector<vector<ll> > dp(h+1, vector<ll>(w+1, 0));
	vector<vector<int> > edge(h+1, vector<int>(w+1, 0));
	vector<int> aux(4,0);
	int i = 1, j = 0, num;
	while(i != bad.size()){
		
		if(bad[i] == ','){
			aux[j] = num;
			num = 0;
			j = 0;
			
			if(aux[1] == aux[3]){
				//can't come from left
				if(edge[aux[1]][max(aux[0], aux[2])] == 0) 
					edge[aux[1]][max(aux[0], aux[2])] = 1;
				else
					edge[aux[1]][max(aux[0], aux[2])] = 3;
				
			}
			else{
				//can't come from down
				if(edge[max(aux[1], aux[3])][aux[0]] == 0) 
					edge[max(aux[1], aux[3])][aux[0]] = 2;
				else
					edge[max(aux[1], aux[3])][aux[0]] = 3;
				
			}
			
		}
		else if(bad[i] == ' ') aux[j++] = num,num = 0;
		else if(bad[i] == '\"');
		else{
			num *= 10;
			num += (bad[i]-'0');
		}
		
		i++;
	}
	
	dp[0][0] = 1;
	for(int i = 0;i <= h;i++){
		for(int j = 0;j <= w;j++){
			
			if(i == 0 || j == 0){
				
				if(i == 0 && j == 0) continue;
				if(edge[i][j] != 0) dp[i][j] = 0;
				else dp[i][j] = (i == 0)?dp[0][j-1]:dp[i-1][0];
				
			}
			else{
				
				if(edge[i][j] == 0) dp[i][j] = dp[i-1][j] + dp[i][j-1];
				else if(edge[i][j] == 1) dp[i][j] = dp[i-1][j];
				else if(edge[i][j] == 2) dp[i][j] = dp[i][j-1];
				
			}
			
		}
	}
	
	/*for(int i = 0;i <= h;i++){
		for(int j = 0;j <= w;j++)  cout<<edge[i][j]<<" ";
		cout<<endl;
	}
	
	for(int i = 0;i <= h;i++){
		for(int j = 0;j <= w;j++)  cout<<dp[i][j]<<" ";
		cout<<endl;
	}*/
	
	return dp[h][w];
}

int main(){
	int w,h;
	string bad;
	scanf("%d %d", &w, &h);
	cin.ignore();
	getline(cin, bad);
	bad[bad.size()-1] = ',';
	
	
	ll ans = numWays(w,h,bad);
	printf("%lld\n", ans);
	return 0;
}

