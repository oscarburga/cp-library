// Sample implicit treap implementation

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int randp() { return uniform_int_distribution<int>(INT_MIN, INT_MAX)(rng); }

struct node {
	int v, p, sz;
	node *L, *R;
	node(int v = 0) : v(v), p(randp()), sz(1), L(nullptr), R(nullptr) {}
} nodes[maxn];
int n, m, node_cnt = 0;

inline int sz(node *t) { return t ? t->sz : 0; }
inline void upd_node(node *t) { if (t) t->sz = 1 + sz(t->L) + sz(t->R); }

inline node* makenode(int v = 0) { 
	nodes[node_cnt] = node(v);
	return &nodes[node_cnt++];
}

pair<node*, node*> split(node *t, int x, int add = 0) {
	if (!t) return { nullptr, nullptr };
	int key = add + sz(t->L) + 1;
	pair<node*, node*> p;
	if (key <= x) {
		p = split(t->R, x, key);
		t->R = p.first;
		upd_node(t);
		return { t, p.second };
	} else {
		p = split(t->L, x, add);
		t->L = p.second;
		upd_node(t);
		return { p.first, t };
	}
}

node *merge(node *t1, node *t2) { // t1 <= t2
	if (!t1) return t2;
	if (!t2) return t1;
	if (t1->p > t2->p) { 
		t1->R = merge(t1->R, t2);
		upd_node(t1);
		return t1;
	} else {
		t2->L = merge(t1, t2->L);
		upd_node(t2);
		return t2;
	}
}

node *kth(node *t, int k) {
	while(t) {
		if (sz(t->L) >= k) { t = t->L; continue; }
		k -= sz(t->L);
		if (k == 1) return t;
		--k;
		t = t->R;
	}
	assert(1==2);
	return nullptr;
}
