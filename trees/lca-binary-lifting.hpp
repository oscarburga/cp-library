// Sample LCA implementation
vector<int> vs[maxn];
int dep[maxn], st[stK][maxn];

void dfs(int u, int p = -1) {
	st[0][u] = p;
	for(int k = 1; (1<<k) <= dep[u]; k++) {
		int v = st[k-1][u];
		st[k][u] = st[k-1][v];
	}
	for(int e: vs[u]) if (e != p) {
		dep[e] = dep[u] + 1;
		dfs(e, u);
	}
}
 
int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int d = dep[u] - dep[v];
	while(d > 0) u = st[__builtin_ctz(d)][u], d &= (d-1);
	if (u == v) return u;
	for(d = stK-1; d >= 0; d--) {
		if (st[d][u] != st[d][v]) {
			u = st[d][u];
			v = st[d][v];
		}
	}
	return st[0][u];
}
