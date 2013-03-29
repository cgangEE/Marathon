#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>
#include <cctype>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <stack>
using namespace std;
typedef vector<int> vi;
typedef vector<string> vs; 
typedef map<int,int> mii;
typedef long long ll;
template <class T> void checkmax(T &t, T x){if (x > t) t = x;}
template <class T> void checkmin(T &t, T x){if (x < t) t = x;}
template <class T> void _checkmax(T &t, T x){if (t == -1 || x > t) t = x;}
template <class T> void _checkmin(T &t, T x){if (t == -1 || x < t) t = x;}
#define INF (INT_MAX/10)
#define SQR(x) ((x)*(x))
#define rep(i, n) for (int i=0; i<(n); ++i)
#define repf(i, a, b) for (int i=(a); i<=(b); ++i)
#define repd(i, a, b) for (int i=(a); i>=(b); --i)
#define iter(v) __typeof((v).begin())
#define foreach(it, v) for (iter(v) it = (v).begin(); it != (v).end(); it++)
#define clr(a, b) memset(a, b, sizeof(a))
#define pb push_back
#define sz(a) ((int)(a).size())
#define all(a) a.begin(), a.end()
#define mid(x, y) ((x+y)/2)
#define vp vector<P>
#define N 50
int i,j,k,m,n,l;
int pay, fine;
struct P{
    int x, y;
    P(){}
    P(int x, int y):x(x),y(y){}
    P operator +(const P&p){ return P(x+p.x, y+p.y); }
    bool ok(){ return (x>=0 && y>=0 && x<n && y<n); }
    void out(){
        cerr<<x<<' '<<y<<endl; }
};

vp work;
bool a[N+10][N+10];
P d[4]={P(-1,0),P(1,0),P(0,-1),P(0,1)}; //up down left right
char c[5]="UDLR";

class SnowCleaning{
public:
    string dtoi(int n){
        vi v; string ret;
        if (!n) v.pb(0);
        while (n) v.pb(n%10), n/=10;
        repd(i, sz(v)-1, 0) ret+=v[i]+'0';        
        return ret;
    }
    int init (int n, int pay, int fine){
        ::n=n, ::pay=pay, ::fine=fine; 
        work.clear(), clr(a, 0), srand(time(NULL));
    }
    vs nextDay(vi s){
        vs ret; 
        rep(i, sz(work)){
            while(1){
                k=rand()%4;
                if ((work[i]+d[k]).ok()){
                    work[i]=work[i]+d[k];
                    ret.pb("M "+dtoi(i)+" "+c[k]);
                    break;
                }
            }
        }
        rep(i, sz(s)/2){
            a[s[i*2]][s[i*2+1]]=1;
            if (rand()%10==0 && sz(work)<100){
                P p(s[i*2], s[i*2+1]); work.pb(p);
                ret.pb("H "+dtoi(p.x)+' '+dtoi(p.y));
            }
        }
        
        return ret;
    }

};

int main(){
    int i,j,k,m,n,l;
    SnowCleaning sc;
    cin>>i>>j>>k;
    sc.init(i,j,k);
    
    rep(i, 2000){
        cin>>n;
        vi v;
        rep(j, n*2) cin>>k, v.pb(k);
        vector<string> vs=sc.nextDay(v);
        cout<<sz(vs)<<endl;
        rep(j, sz(vs)) cout<<vs[j]<<endl;
        cout.flush();
    }
}
