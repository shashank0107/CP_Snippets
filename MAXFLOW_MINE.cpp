struct MF {
    int n;
    vector<vector<int> > adj, cap;
    vector<int> vis;

    MF(int nn) {
        n = nn;
        adj.resize(n);
        vis.resize(n);
        cap = vector<vector<int> >(n, vector<int>(n, 0));
    }
    void insertEdge(int s, int e, int capacity) {
        adj[s].pb(e);
        adj[e].pb(s);
        cap[s][e] = capacity;
        cap[e][s] = capacity;
    }
    int bfs(int s, int e, vector<int>& parent) {
        fill(all(parent), -1);
        parent[s] = -2;
        queue<PII> q;
        q.push(mp(s, INT_MAX));

        while (!q.empty()) {
            PII p = q.front();  q.pop();
            int cur = p.F;
            int flow = p.S;

            for (auto next : adj[cur]) {
                if (parent[next] == -1 && cap[cur][next]) {
                    parent[next] = cur;
                    int newflow = min(flow, cap[cur][next]);
                    if (next == e)
                        return newflow;
                    q.push(mp(next, newflow));
                }
            }
        }
        return 0;
    }
    int maxFlow(int source, int sink) {
        int flow = 0;
        vector<int> parent(n);
        int newflow;

        while (newflow = bfs(source, sink, parent)) {
            flow += newflow;

            for (int cur = sink; cur != source; cur = parent[cur]) {
                int prev = parent[cur];
                cap[prev][cur] -= newflow;
                cap[cur][prev] += newflow;
            }
        }
        return flow;
    }
    void dfs(int v, vector<PII>& ans) {
        vis[v] = 1;
        for (auto nb : adj[v])
            if (vis[nb] == 0) {
                dfs(nb, ans);
            }
            else if (vis[nb] == 2)
                ans.pb(mp(v,nb));
    }
    void dfs2(int v) {
        vis[v] = 2;
        for (auto nb : adj[v]) 
            if (!vis[nb] && cap[nb][v] > 0) dfs2(nb);
    }
    vector<PII> getMinCut(int source, int sink) {
        fill(all(vis), 0);
        
        vector<PII> ans;
        dfs2(sink);
        dfs(source, ans);
        return ans;
    }
};
