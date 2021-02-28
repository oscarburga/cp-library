// Sample HLD implementation for reference.
// For edge upd/queries, remember to adjust last line in query and upd

namespace HLD { 
	vector<int> vs[maxn];
	int tmr, p[maxn], dep[maxn], head[maxn], sz[maxn], tin[maxn];
	void dfs(int v) { 
		sz[v] = 1;
		for(int i = 0, e; i<int(vs[v].size()); ++i) {
			e = vs[v][i];
			if (e == p[v]) {
				swap(vs[v].back(), vs[v][i--]); 
				vs[v].pop_back();
				continue;
			}
			p[e] = v;
			dfs(e);
			sz[v] += sz[e];
			if (sz[e] > sz[vs[v][0]]) swap(vs[v][i], vs[v][0]);
		}
	}
	void hld(int v) {
		tin[v] = tmr++;
		for(int e: vs[v]) {
			head[e] = e == vs[v][0] ? head[v] : e;
			dep[e] = dep[v] + 1;
			hld(e);
		}
	}
	int path_query(int u, int v) {
		int res = NEUTRAL
		while(head[u] != head[v]) {
			if (dep[head[u]] < dep[head[v]]) swap(u, v);
			res = merge_ans(res, query(tin[head[u]], tin[u]));
			u = p[head[u]];
		}
		if (dep[u] < dep[v]) swap(u, v);
		return max(res, query(tin[v], tin[u]));
	}
	void path_upd(int u, int v, int k) {
		while(head[u] != head[v]) {
			if (dep[head[u]] < dep[head[v]]) swap(u, v);
			upd(tin[head[u]], tin[u], k);
			u = p[head[u]];
		}
		if (dep[u] < dep[v]) swap(u, v);
		upd(tin[v], tin[u], k);
	}
}
