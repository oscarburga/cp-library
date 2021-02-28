// Sample Centroid Decomposition implementation for reference

int sz[maxn], par[maxn], ans[maxn];
vector<int> vs[maxn], ct[maxn], dis[maxn];

int dfs_sz(int v, int p = -1) {
	sz[v] = 1;
	for(int e: vs[v]) if (e != p && !removed[e]) sz[v] += dfs_sz(e, v);
	return sz[v];
}

int centroid(int v, int p, int tsz) {
	for(int e: vs[v]) 
		if (e != p && !removed[e] && (sz[e] << 1) > tsz)
			return centroid(e, v, tsz);
	return v;
}

void dfs_c(int v, int p, int d) {
	dis[v].emplace_back(d++);
	for(int e: vs[v]) if (e != p && !removed[e]) dfs_c(e, v, d);
}

void decompose(int v, int p = -1) {
	int c = centroid(v, -1, dfs_sz(v));
	par[c] = p;
	if (p != -1) ct[p].emplace_back(c);
	removed[c] = true;
	//solve(c); if needed
	for(int e: vs[c]) if (!removed[e]) dfs_c(e, c, 1);
	for(int e: vs[c]) if (!removed[e]) decompose(e, c);
}

void upd(int v) {
	for(int u = v, anc = 0; u != -1; u = par[u], ++anc) 
		ans[u] = min(ans[u], dis[v][anc]);
}

int query(int v) {
	int res = inf;
	for(int u = v, anc = 0; u != -1; u = par[u], ++anc)
		res = min(res, ans[u] + dis[v][anc]);
	return res;
}

void init_cdt() {
	decompose(1);
	for(int i = 1; i<=n; i++) {
		ans[i] = inf;
		dis[i].emplace_back(0);
		reverse(dis[i].begin(), dis[i].end());
	}
}
