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

const int N = 50;

struct e_t {int to, cap, rev, cost;}; 

// -------------------------Minimal Cost Maximal Flow        ------------------------------------------------------------------------
template <int N>
class MCMF{           
public:          
vector<e_t> a[N*5+10]; 
int f[N*5+10], c[N*5+10];
bool inQ[N*5+10];
e_t *e[N*5+10];
int s, t;

void clear(){ rep(i, t+1) a[i].clear(); }

void add(int i, int j, int c, int cost){ 
        a[i].pb((e_t){j, c, sz(a[j]), cost}); 
        a[j].pb((e_t){i, 0, sz(a[i])-1, -cost}); 
} 

bool bellmanFord(int &flow, int &cost){
    queue<int> q; 
    clr(f, 0), clr(c, 0x7f), clr(inQ, 0);
    
    q.push(s), f[s]=INF, c[s]=0, inQ[s]=1;
    while (!q.empty()){
        int i=q.front(); q.pop(); inQ[i]=0;
        rep(k, sz(a[i])){
            e_t & ei = a[i][k];
            if (ei.cap && c[ei.to]>c[i]+ei.cost){
                f[ei.to]=min(f[i], ei.cap);
                c[ei.to]=c[i]+ei.cost;
                e[ei.to]=&ei;                
                if (!inQ[ei.to]) inQ[ei.to]=true, q.push(ei.to);
            }
            
        }
    }
    if (c[t]==0x7f7f7f7f) return false;
    flow+=f[t], cost+=c[t]*f[t];
    int i=t;
    while (i!=s){
        e[i]->cap-=f[t];
        a[i][e[i]->rev].cap+=f[t];
        i=a[i][e[i]->rev].to;
    }
    return true;
}

void minCost(int &flow, int &cost){
    while (bellmanFord(flow, cost));    
}

};

// ----------------------------------------------------------------------------------------------------------------------------------
MCMF<N*100> mcmf;


int i,j,k,m,n,l;
int pay, fine;
struct P{
    int x, y;
    P(){}
    P(int x, int y):x(x),y(y){}
    P operator +(const P&p){ return P(x+p.x, y+p.y); }
    bool ok(){ return (x>=0 && y>=0 && x<n && y<n); }
    int mht(P &p){ return abs(x-p.x)+abs(y-p.y); }
    void out(){cerr<<x<<' '<<y<<endl; }
};

vp work;
bool SNOW[N+10][N+10];
bool f[N*N+10];
P d[4]={P(-1,0),P(1,0),P(0,-1),P(0,1)}; //up down left right
char c[5]="UDLR";
int x, y;

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
        work.clear(), clr(SNOW, 0), srand(time(NULL));
    }
    vs nextDay(vi s){
        vp snow; vs ret;
        
        rep(i, sz(s)/2) SNOW[s[i*2]][s[i*2+1]]=1;
        rep(i, n) rep(j, n) if (SNOW[i][j]) snow.pb(P(i,j));
        
        mcmf.s=sz(work)+sz(snow), mcmf.t=mcmf.s+1;
        mcmf.clear();

        rep(i, sz(work)) rep(j, sz(snow)) mcmf.add(i, sz(work)+j, 1, work[i].mht(snow[j]));
        rep(i, sz(work)) mcmf.add(mcmf.s, i, 1, 0);
        rep(i, sz(snow)) mcmf.add(i+sz(work), mcmf.t, 1, 0);
        int flow, cost;
        mcmf.minCost(flow, cost);
        
        clr(f, 0);
        rep(i, sz(work))
            rep(j, sz(mcmf.a[i])){
                e_t e=mcmf.a[i][j];  
                int j=e.to-sz(work);
                if (e.cap==0 && j>=0 && j<sz(snow)){
                    if (work[i].x!=snow[j].x){
                        if (work[i].x<snow[j].x) 
                            work[i].x++, ret.pb("M "+dtoi(i)+" D");
                        else
                            work[i].x--, ret.pb("M "+dtoi(i)+" U");
                    }
                    else if (work[i].y!=snow[j].y){
                        if (work[i].y<snow[j].y)
                            work[i].y++, ret.pb("M "+dtoi(i)+" R");
                        else
                            work[i].y--, ret.pb("M "+dtoi(i)+" L");
                    }
                    f[j]=1;
                    SNOW[work[i].x][work[i].y]=0;
                    
                /*    cerr<<i<<' '<<j<<endl;
                    cerr.flush();
                    */
                }
            }
        
        int mw=min(100, fine*(sz(snow))/pay/3);
        snow.clear();
        rep(i, n) rep(j, n) if (SNOW[i][j]) snow.pb(P(i,j));
        rep(i, sz(snow)) if (sz(work)<mw && !f[i]){
            work.pb(snow[i]), ret.pb("H "+dtoi(snow[i].x)+' '+dtoi(snow[i].y));
            SNOW[snow[i].x][snow[i].y]=0;
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
