// Sample Treap implementation

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int randp() { return uniform_int_distribution<int>(INT_MIN, INT_MAX)(rng); }

const int maxn = 2e5+5;
int node_cnt = 0;
struct node {
	int k, p, sz = 1;
	node *L = nullptr, *R = nullptr;
	node(){}
	node(int k) : k(k), p(randp()) {}
} nodes[maxn];

node *makenode(int x) { 
	nodes[node_cnt] = node(x);
	return &nodes[node_cnt++];
}

inline int sz(node *t) { return t ? t->sz : 0; }
inline void upd(node *t) { if (t) t->sz = 1 + sz(t->L) + sz(t->R); }

pair<node*, node*> split(node *t, int x) {
	if (!t) return { nullptr, nullptr };
	pair<node*, node*> p;
	if (t->k <= x) {
		p = split(t->R, x);
		t->R = p.first;
		upd(t);
		return { t, p.second };
	} else {
		p = split(t->L, x);
		t->L = p.second;
		upd(t);
		return { p.first, t };
	}
}

node *merge(node *t1, node *t2) {
	if (!t1) return t2;
	if (!t2) return t1;
	if (t1->p > t2->p) {
		t1->R = merge(t1->R, t2);
		upd(t1);
		return t1;
	} else {
		t2->L = merge(t1, t2->L);
		upd(t2);
		return t2;
	}
}

void insert(node *&t, int x) {
	auto p = split(t, x);
	t = merge(merge(p.first, makenode(x)), p.second);
}

int order_of_key(node *t, int x) {
	int res = 0;
	while(t) {
		if (t->k <= x) res += sz(t->L) + 1, t = t->R;
		else t = t->L;
	}
	return res;
}

void report_kth(node *t, int k) {
	if (sz(t) < k) { puts("invalid"); return; }
	while(t) {
		if (sz(t->L) >= k) { t = t->L; continue; }
		k -= sz(t->L);
		if (k == 1) { printf("%d\n", t->k); return; }
		t = t->R;
		k--;
	}
	assert(1==2);
}
