/* Link to the problem:
https://www.codechef.com/problems/D2/
*/

#include<bits/stdc++.h>
using namespace std;

int lis(vector<int> &num, int id, int n){
	vector<int> dp(n,0);
	dp[0] = 1;
	for(int i = id+1;i < id+n; i++){
		for(int j = id;j < i;j++){
			if(num[j] < num[i]){
				dp[i-id] = max(dp[i-id], dp[j-id]);
			}
		}
		dp[i-id]++;
	}
	
	for(int i = 1;i < n;i++)
		dp[0] = max(dp[0],dp[i]);
	
	return dp[0];
}

int main(){
	int t,n,ans;
	scanf("%d",&t);
	while(t--){
		ans = 0;
		scanf("%d",&n);
		vector<int> num(2*n);
		
		for(int i = 0;i < n;i++){
			scanf("%d", &num[i]);
			num[i+n] = num[i];
		}
		
		for(int i = 0;i < n;i++)
			ans = max(ans, lis(num,i,n));
		printf("%d\n", ans);
	}
}

