vector <int> sort_shifts(string const &s) {
    const int alphabet = 256;
	int n = s.size();

	vector <int> p(n), c(n), cnt(alphabet);
	for (int i = 0; i < n; i++) 
		cnt[s[i]]++;
	for (int i = 1; i < alphabet; i++) 
		cnt[i] += cnt[i - 1];
	for (int i = 0; i < n; i++)
		p[--cnt[s[i]]] = i;
	int id = 0;
	for (int i = 0; i < n; i++) {
		if (i && s[p[i]] != s[p[i - 1]]) ++id;
		c[p[i]] = id;
	}

	int k = 0;
	auto get = [&] (int p) {
		return make_pair(c[p], c[(p + (1 << k)) % n]);
	};
	auto cmp = [&] (int x, int y) {
		return get(x) < get(y);
	};

	for (int dg = 0, len = 1; len <= n; dg++, len <<= 1) {
		k = dg;
		sort(p.begin(), p.end(), cmp);
		id = 0;
		vector <int> nc(n);
		for (int i = 0; i < n; i++) {
			if (i && get(p[i]) != get(p[i - 1])) ++id;
			nc[p[i]] = id;
		}
		c = nc;
	}
	return p;
} 
vector <int> build_sa(string s) {
	s += "$";
	vector <int> res = sort_shifts(s);
	res.erase(res.begin());
	return res;
}
vector <int> build_lcp(const string &s, const vector <int> &p) {
	int n = s.size();
	vector <int> rank(n, 0);
	for (int i = 0; i < n; i++) 
		rank[p[i]] = i;
	int k = 0;
	vector <int> res(n, 0);
	for (int i = 0; i < n; i++) {
		if (rank[i] == n - 1) {
			k = 0;
			continue;
		}
		int j = p[rank[i] + 1];
		while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
		res[rank[i]] = k;
		if (k) k--;
	}
	return res;
} 
