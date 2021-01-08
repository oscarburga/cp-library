//I want to rewrite it eventually to make it shorter & prettier
struct aho {
	int nodes;
	vector<array<int, 26>> go;
	vector<int> term, suf;
	aho() : nodes(1), go({{}}), term({0}) {}
	void insert(string& s){
		int pos = 0;
		for(char c: s) {
			char nxt = c - 'a';
			if (!go[pos][nxt]) {
				go[pos][nxt] = nodes++;
				go.push_back({});
				term.push_back(0);
			}
			pos = go[pos][nxt];
		}
		term[pos]++;
	}

	void build(){
		suf.resize(nodes, 0);
		queue<int> q;
		q.emplace(0);
		while(q.size()){
			int u = q.front(); q.pop();
			for(char c = 'a'; c <= 'z'; c++){
				char nxt = c - 'a';
				if (go[u][nxt]){
					suf[go[u][nxt]] = u ? go[suf[u]][nxt] : 0;
					q.emplace(go[u][nxt]);
				} else go[u][nxt] = u ? go[suf[u]][nxt] : 0;
			}
		}
	}
};
