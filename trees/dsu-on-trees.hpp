// Sample Sack / DSU on trees implementation

int n, q, sz[maxn], cnt[maxn];
vector<int> vs[maxn];

void dfs(int v) {
	sz[v] = 1;
	for(int i = 0, e; i<int(vs[v].size()); i++) {
		e = vs[v][i];
		dep[e] = dep[v] + 1;
		dfs(e);
		sz[v] += sz[e];
		if (sz[vs[v][0]] < sz[e]) swap(vs[v][0], vs[v][i]);
	}
}

void add(int v, int x, bool skip_big) {
	cnt[f(v)] += x;
	for(int i = skip_big; i<(int)vs[v].size(); i++) add(vs[v][i], x, 0);
}

void solve(int v, bool keep = true) {
	for(int i = 1; i<(int)vs[v].size(); i++) solve(vs[v][i], 0);
	if (vs[v].size()) solve(vs[v][0], 1);
	add(v, 1, 1);
	//answer queries
	if (!keep) add(v, -1, 0);
}
