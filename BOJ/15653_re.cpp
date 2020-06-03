#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <tuple>
using namespace std;
int n,m;
char a[11][11];
int d[11][11][11][11];
const int dx[]={0,0,1,-1}, dy[]={1,-1,0,0};
struct position{
    int rx,ry,bx,by;
};
pair<bool, bool> simulate(vector<string> &a, int k, int &x, int &y){
    if(a[x][y]=='.') return make_pair(false, false);
    bool moved =false;
    while(true){
        int nx = x+dx[k],ny=y+dy[k];
        if(nx <0 || nx >= n || ny<0 || ny>=m) return make_pair(moved,false);
        if(a[nx][ny]=='#') return make_pair(moved,false);
        else if (a[nx][ny]=='R'|| a[nx][ny]=='B') return make_pair(moved,false);
        else if (a[nx][ny]=='.'){
            swap(a[nx][ny],a[x][y]);
            x=nx, y =ny;
            moved=true;
        }else if (a[nx][ny]=='O'){
            a[x][y]='.';
            moved=true;
            return make_pair(moved,true);
        }
    }
    return make_pair(false,false);
}
pair<bool, bool> next (vector<string> a, int &rx, int &ry,int &bx, int &by,int dir){
    a[rx][ry]='R';
    a[bx][by]='B';
    bool hole1=false, hole2=false;
    while(true){
        // p1,2는 pair, first =움직였는지, second= 구멍에 들어갔는지
        auto p1 = simulate(a,dir,rx,ry);
        auto p2 = simulate(a, dir,bx,by);
        //둘 다 안 움직였으면 break;
        if(p1.first == false && p2.first ==  false) break;
        if(p1.second) hole1=true;
        if(p2.second) hole2=true;
    }
    return make_pair(hole1,hole2);
}
int main(){
    int rx,ry,bx,by,hx,hy;
    cin >> n >> m;
    vector<string> a(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='O'){
                hx=i;hy=j;
            }else if (a[i][j]=='R'){
                rx=i;ry=j;
                a[i][j]='.';
            }else if (a[i][j]=='B'){
                bx=i;by=j;
                a[i][j]='.';
            }
        }
    }
    memset(d,-1,sizeof(d));
    int ans = -1;
    queue<position> q;
    q.push({rx,ry,bx,by});
    d[rx][ry][bx][by]=0;
    bool found = false;
    while(!q.empty()){
        int rx = q.front().rx, ry=q.front().ry;
        int bx=q.front().bx,by=q.front().by;
        q.pop();
        for(int k=0;k<4;k++){
            int nrx = rx, nry=ry,nbx=bx,nby=by;
            pair<bool,bool> holes = next(a,nrx,nry,nbx,nby,k);
            if(holes.second) continue; // 파란공이 구멍에 빠진 경우 pass
            if(holes.first){
                found = true;
                ans = d[rx][ry][bx][by]+1;
                break;
            }
            if(d[nrx][nry][nbx][nby]!=-1) continue; //이미 방문한 경우
            q.push({nrx,nry,nbx,nby});
            d[nrx][nry][nbx][nby]= d[rx][ry][bx][by]+1;
        }
        if(found) break;
    }
    printf("%d\n",ans);
    return 0;
}