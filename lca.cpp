#include <bits/stdc++.h>
#define gc getchar_unlocked()
#define pc(x) putchar_unlocked(x)
template<typename T> void scan(T &x){x = 0;register bool _=0;register T c=gc;_=c==45;c=_?gc:c;while(c<48||c>57)c=gc;for(;c<48||c>57;c=gc);for(;c>47&&c<58;c=gc)x=(x<<3)+(x<<1)+(c&15);x=_?-x:x;}
template<typename T> void printn(T n){register bool _=0;_=n<0;n=_?-n:n;char snum[65];int i=0;do{snum[i++]=n%10+48;n/= 10;}while(n);--i;if (_)pc(45);while(i>=0)pc(snum[i--]);}
template<typename First, typename ... Ints> void scan(First &arg, Ints&... rest){scan(arg);scan(rest...);}
template<typename T> void print(T n){printn(n);pc(10);}
template<typename First, typename ... Ints> void print(First arg, Ints... rest){printn(arg);pc(32);print(rest...);}

using namespace std;
const int MM = 1e5+1, LOG = 20;

int n, dep[MM], sp[LOG][MM], val[LOG][MM];

int getlca(int u, int v){
    if(dep[u] < dep[v])
        swap(u, v);
    //u gets jumped up
    for(int i = LOG-1; i >= 0; i--){
        if(~sp[i][u] && (dep[sp[i][u]] >= dep[v]))
            u = sp[i][u];
    }
    //now should be on same level
    if(u == v)
        return u;
    for(int i = LOG-1; i >= 0; i--){
        if(~sp[i][u] && ~sp[i][v] && (sp[i][u] != sp[i][v])){
            u = sp[i][u];
            v = sp[i][v];
        }
    }
    return sp[0][u];
    //return direct parent
}

//binary lift

int query(int a, int b){
    
    int lcan = getlca(a, b), ret = 0;
    
    for(int i = LOG-1; i >= 0; i--){
        if(dep[a] >= dep[lcan] + (1<<i)){
            ret = max(ret, val[i][a]);
            a = sp[i][a];
        }
    }
    
    for(int i = LOG-1; i >= 0; i--){
        if(dep[b] >= dep[lcan] + (1<<i)){
            ret = max(ret, val[i][b]);
            b = sp[i][b];
        }
    }
    return ret;
}

int main(){
    
    memset(sp, -1, sizeof sp);
    
    //dfs
    
    for(int i = 1; i < LOG; i++){
        for(int j = 0; j <= n; j++){
            if(~sp[i-1][j]){
                sp[i][j] = sp[i-1][ sp[i-1][j] ];
                val[i][j] = max(val[i-1][j], val[i-1][ sp[i-1][j] ]);
            }
        }
    }
    
    return 0;
}
