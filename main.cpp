#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using Adj = vector<vii>;

constexpr auto inf = int{ 987'654'321 };

int n, m, r;
vi nitem;
Adj adj;
int ans;

vi dijk(int b) {
	auto dist = vi(n + 1, inf);
	dist[b] = 0;

	auto q = priority_queue<pii, vii, greater<pii>>{};
	q.push({ 0, b });
	while (!q.empty()) {
		const auto& [_, x] = pii{ q.top() };
		q.pop();

		for (const auto& [y, c] : adj[x]) {
			const auto& newDist = dist[x] + c;
			if (newDist < dist[y]) {
				dist[y] = newDist;
				q.push({ dist[y], y });
			}
		}
	}

	return dist;
}

void solve() {
	for (auto b = 1; b <= n; ++b) {
		const auto& dist = dijk(b);

		auto count = int{ 0 };
		for (auto i = 1; i <= n; ++i) {
			if (dist[i] <= m) {
				count += nitem[i];
			}
		}

		ans = max(ans, count);
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m >> r;

	nitem = vi(n + 1, 0);
	for (auto i = 1; i <= n; ++i) {
		cin >> nitem[i];
	}

	adj = Adj(n + 1, vii{});
	for (auto i = 0; i < r; ++i) {
		int a, b, c;
		cin >> a >> b >> c;

		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}

	solve();
	cout << ans;

	return 0;
}