
#include<bits/stdc++.h>

typedef long long LL;
using namespace std;
const int M = 1000000007;
struct matrix {
	LL a[2][2];
	matrix() {
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				a[i][j] = 0;
	}
	matrix operator*(matrix x) {
		matrix ans;
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j) {
				for (int k = 0; k < 2; ++k)
					ans.a[i][j] = (ans.a[i][j] + a[i][k] * x.a[k][j]) % M;
			}
		return ans;
	}
};


matrix pw(matrix a, LL b) {
	matrix ans;
	for (int i = 0; i < 2; ++i)
		ans.a[i][i] = 1;
	while (b) {
		while (!(b & 1))
			b >>= 1, a = a * a;
		--b;
		ans = ans * a;
	}
	return ans;
}


int main() {
	matrix a;
	LL a1,b1,n,x;
	cin>>a1>>b1>>n>>x;

	a.a[0][0] = a1;
	a.a[0][1] = b1;
	a.a[1][0] = 0;
	a.a[1][1] = 1;

	a = pw(a, n);

	//cout<<a.a[0][0]<<' '<<a.a[0][1]<<' '<<a.a[1][1]<<' '<<a.a[1][0]<<endl;

	LL ans = (a.a[0][0]*x + a.a[0][1]);
	ans %= M;
	cout << ans << "\n";
	return 0;
}

