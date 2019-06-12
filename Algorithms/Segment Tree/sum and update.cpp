/*
	* Description:
		* Tree can make updates on range and get sum on range
*/


const int N = (int)1e5 + 7;

struct tree {
	long long t[N << 2], u[N << 2];
	void push(int v, int tl, int tr) {
		if (u[v]) {
			int tm = tl + tr >> 1;
			t[v << 1] += (tm - tl + 1) * u[v];
			t[v << 1 | 1] += (tr - tm) * u[v];
			u[v << 1] += u[v];
			u[v << 1 | 1] += u[v];
			u[v] = 0;
		}
	}
	void upd(int l, int r, int x, int v, int tl, int tr) {
		if (l <= tl && tr <= r) {
			t[v] += (long long)x * (tr - tl + 1);
			u[v] += x;
			return;
		}
		if (tl > r || tr < l) return;
		int tm = tl + tr >> 1;
		push(v, tl, tr);
		upd(l, r, x, v << 1, tl, tm);
		upd(l, r, x, v << 1 | 1, tm + 1, tr);
		t[v] = t[v << 1] + t[v << 1 | 1];
	}
	long long get(int l, int r, int v, int tl, int tr) {
		if (l <= tl && tr <= r) return t[v];
		if (tl > r || tr < l) return 0;
		int tm = tl + tr >> 1;
		push(v, tl, tr);
		return get(l, r, v << 1, tl, tm) + get(l, r, v << 1 | 1, tm + 1, tr);
	}
};
