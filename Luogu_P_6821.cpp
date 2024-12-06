#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define FL(a, b, c) for(int a = (b), a##end = (c); a <= a##end; a++)
#define FR(a, b, c) for(int a = (b), a##end = (c); a >= a##end; a--)
#define int long long
constexpr int N = 1e6 + 10;
int a[N], sum, n, pr[N];
int f(int x){
	sum = 0;
	int s = 0, w = 0;
	FL(i, 1, n){
		if(a[i] < 0){
			int j = i;
			while(a[j + 1] < 0)j++;
			if(pr[j] - pr[i - 1] + x >= 0)w += pr[j] - pr[i - 1];
			else sum += w + x, s++, w = 0;
			i = j;
		}
		else w += a[i];
	}
	if(w)s++, sum += w + x;
	return s;
}
int32_t main(){
	//cin.tie(0)->sync_with_stdio(0);
	int k;
	cin >> n >> k;
	FL(i, 1, n)cin >> a[i], pr[i] = pr[i - 1] + a[i];
	int l = -1e6, r = 1e16, ans = 0;
	while(l <= r){
		int mid = l + r >> 1;
		int s = f(mid);
		if(s >= k){
			priority_queue<int, vector<int>, greater<int>>q;
			sum = 0;int s = 0, w = 0;
			FL(i, 1, n){
				if(a[i] < 0){
					int j = i;
					while(a[j + 1] < 0)j++;
					if(pr[j] - pr[i - 1] + mid >= 0)w += pr[j] - pr[i - 1];
					else sum += w + mid, q.emplace(w + mid), s++, w = 0;
					i = j;
				}
				else w += a[i];
			}
			if(w)s++, sum += w + mid, q.emplace(w + mid);
			if(s > k)l = mid + 1;
			else r = mid - 1;
			while(s > k || (s && q.top() < mid)){
				sum -= q.top(), s--;
				q.pop();
			}
			ans = max(ans, sum - k * mid);
		}
		else r = mid - 1, ans = max(ans, sum - s * mid);
	}
	cout << ans << endl;
	return 0;
}