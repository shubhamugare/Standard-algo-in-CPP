#include <bits/stdc++.h>

using namespace std;

const int mod = 7340033;
const int r = 2187;
const int K = 21;
const int X = 20;
const int N = 1 << X;
const int M = (int)1e9+7;
typedef long long ll;


//NTT modulo --{ mod  = 7340033}

LL rPower[2][K];
int reversedBits[N];
LL A[N], B[N];

void pre()
{
    rPower[0][K - 1] = r;
    rPower[1][K - 1] = inv(r);
    for (int j = 0; j < 2; ++j)
    for (int i = K - 2; i >= 0; --i)
        rPower[j][i] = powa(rPower[j][i + 1], 2);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < X; ++j)
            if ((i >> j) & 1)
                reversedBits[i] |= (1 << (X - j));
}

LL powa(LL x, LL a) 
{
    x %= mod;
    LL y = 1;
    while (a) {
        if (a & 1)
            y = (y * x) % mod;
        x = (x * x) % mod;
        a >>= 1;
    }
    return y;
}

LL inv(LL x) {
    return powa(x, mod - 2);
}

void pre() {
    rPower[0][K - 1] = r;
    rPower[1][K - 1] = inv(r);
    for (int j = 0; j < 2; ++j)
    for (int i = K - 2; i >= 0; --i)
        rPower[j][i] = powa(rPower[j][i + 1], 2);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < X; ++j)
            if ((i >> j) & 1)
                reversedBits[i] |= (1 << (X - j));
}

int reverseBits(int x, int ns) {
    return reversedBits[x] >> (X - ns + 1);
}

void fft(LL *a, int n, int ns, LL *power) {
    for (int i = 0; i < n; ++i)
        if (reverseBits(i, ns) > i)
            swap(a[i], a[reverseBits(i, ns)]);

    for (int j = 0; j < ns; ++j)
        for (int i = 0; i < n; i += (1 << (j + 1))) {
            LL p = 1, e = power[j + 1];
            for (int k = 0; k < (1 << j); ++k) {
                LL x = a[i + k], y = a[i + k + (1 << j)];
                a[i + k] = (x + p * y) % mod;
                a[i + k + (1 << j)] = (x - p * y) % mod;
                p = (p * e) % mod;
            }
        }
}

void mul(LL *a, LL *b, LL *c, int ns) {
    fft(a, 1 << ns, ns, rPower[0]);
    fft(b, 1 << ns, ns, rPower[0]);
    for (int i = 0; i < (1 << ns); ++i)
        c[i] = (a[i] * b[i]) % mod;
    fft(c, 1 << ns, ns, rPower[1]);
    LL in = inv(1 << ns);
    for (int i = 0; i < (1 << ns); ++i) {
        c[i] = (c[i] * in) % mod;
        if (c[i] < 0)
            c[i] += mod;
    }
}

int n, a, b, c;
LL f[N], fr[N];

LL choose(LL n, LL k) {
    if (k < 0 || n < k)
        return 0;
    return (f[n] * fr[k] % mod) * fr[n - k] % mod;
}


int main() 
{   
    pre();
    mul(A, B, A, ns);
}
