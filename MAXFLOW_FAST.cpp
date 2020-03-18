namespace Maxflow{
    const int maxn=2022;
    const int maxm=66666;
    const int inf=1000000000;
 
    int g[maxn],to[maxm],np[maxm],cp;
    int n,u,v,now,source,sink;
    int sum,cap[maxm],a[maxn];
    int d[maxn],p[maxn],cur[maxn],cnt[maxn];
 
    void add_edge(int x,int y,int z){
//        printf("%d - %d: %d\n",x,y,z);
        cap[cp]=z;to[cp]=y;np[cp]=g[x];g[x]=cp++;cap[cp]=0;to[cp]=x;np[cp]=g[y];g[y]=cp++;
    }
 
    void init(){
        cp=2; memset(g,0,sizeof(g));
    }
    int maxflow(){
        sum=0;
        for(u=1;u<=n;u++)cur[u]=g[u]; a[u=source]=inf; memset(d,0,sizeof(int)*(n+1)); memset(cnt,0,sizeof(int)*(n+1)); cnt[0]=n;
        while(d[source]<n)
        {
            for(now=cur[u];now;now=np[now])if(cap[now]&&d[v=to[now]]+1==d[u])break; cur[u]=now;
            if(now)
            {
                p[v]=now; a[v]=cap[now]; if(a[v]>a[u])a[v]=a[u];
                if((u=v)==sink)
                {
                    do{cap[p[u]]-=a[sink]; cap[p[u]^1]+=a[sink]; u=to[p[u]^1];}while(u!=source);
                    sum+=a[sink]; a[source]=inf;
                }
            }
            else
            {
                if(--cnt[d[u]]==0)break; d[u]=n; cur[u]=g[u];
                for(now=g[u];now;now=np[now]) if(cap[now] && d[u]>d[to[now]]+1) d[u]=d[to[now]]+1;
                cnt[d[u]]++;
                if(u!=source)u=to[p[u]^1];
            }
        }
    //    printf("maxflow\n");
        return sum;
    }
}
