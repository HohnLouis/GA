#include <bits/stdc++.h>

using namespace std;

const int M = 1000, mod = 54;
vector<string> P(M + 1), Q;
vector<int> f(M + 1), F(M + 1);
int cnt = 0;

double pc = 0.6, pm = 0.03;
//xac suat lai ghep va dot bien

string rand_str()
{
    string s = "";
    int check = 0;
    for(int i = 0; i < 12; i++)
    {
        int a = rand() % (6 - 1 + 1) + 1;
        s += char(a + 48);
    }
    return s;
}
//sinh ngau nhien ca the

void creation()
{
    srand(time(0));
    for(int i = 1; i <= M; i++) P[i] = rand_str();
    cout << "Quan the ban dau:\n";
    for(int i = 1; i <= M; i++) cout << P[i] << '\n';
}
//Khoi tao quan the ban dau co 1000 ca the

int adaptive_value(string &s)
{
    long long res = 0;
    for(int i = 1; i <= 12; i++)
    {
        int a = pow(s[i - 1] - 48, i);
        res = (res + a) % 54;
    }
    return res;
}
//ham thich nghi

void adaptability()
{
    F[0] = f[0] = 0;
    for(int i = 1; i <= M; i++)
    {
        f[i] = adaptive_value(P[i]);
        F[i] = F[i - 1] + f[i];
    }
}
//tinh do thich nghi f(xi) va F

void regeneration()
{
    srand(time(0));
    vector<string> Pt;
    while(Pt.size() < M)
    {
        int q = rand() % (F[M] - 0 + 1) + 0;
        int k = lower_bound(F.begin(), F.end(), q) - F.begin();
        Pt.push_back(P[k]);
    }
    P = Pt;
}
//toan tu chon loc

void mutation(string &s)
{
    for(char i: s)
    {
        double pi = rand() % (1 - 0 + 1) + 0;
        if(pi < pm) i = char(55 - i);
    }
}
//toan tu dot bien

void hybridization()
{
    for(int i = 1; i <= M; i++)
    {
        double r = rand() % (1 - 0 + 1) + 0;
        if(r < pc) Q.push_back(P[i]);
    }
    srand(time(0));
    for(int i = 1; i <= 500; i++)
    {
        int p1 = rand() % (11 - 1 + 1);
        int p2 = rand() % ((11 - p1) -1 + 1) + 1;
        string x1 = P[i].substr(0, p1 - 1) + P[501 - i].substr(p1, p2) + P[i].substr(p1 + p2, 10 - p1 - p2);
        string x2 = P[501 - i].substr(0, p1 - 1) + P[i].substr(p1, p2) + P[501 - i].substr(p1 + p2, 10 - p1 - p2);
        mutation(x1);
        mutation(x2);
        P.push_back(x1);
        P.push_back(x2);
    }
}
//toan tu lai ghep

void xuat()
{
    cout << "So lan lai ghep: " << cnt << '\n';
    cout << "Do thich nghi quan the: " << F[M] << '\n';
    int ma = max_element(f.begin(), f.end()) - f.begin();
    cout << "Cong thuc hieu qua nhat: " << P[ma] << " (f=" << f[ma] << ')';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("GA.inp", "r", stdin);
    //freopen("GA.out", "w", stdout);
    creation();
    adaptability();
    do
    {
        regeneration();
        hybridization();
        adaptability();
        cnt++;
    }
    while(F[M] < 32000);
    xuat();
    return 0;
}
