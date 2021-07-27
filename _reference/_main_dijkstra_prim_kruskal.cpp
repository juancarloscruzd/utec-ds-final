#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class DSU {
	private:
		int n;
		vector<int> par;
		vector<int> rank;

	public:
		DSU(int n): n(n), par(n), rank(n, 0) {
			for (int i = 0; i < n; i++)
				par[i] = i;
		}

		int root(int x) {
			while (par[x] != x) {
				par[x] = par[par[x]];
				x = par[x];
			}
			return x;
		}

		bool join(int x, int y) {
			x = root(x);
			y = root(y);

			if (x == y)
				return false;

			if (rank[x] < rank[y])
				swap(x, y);

			par[y] = x;
			if (rank[y] == rank[x])
				rank[x]++;

			return true;
		}
};

class Graph {
	private:
		class Edge {
			public:
				int u, v, w;

				bool operator<(const Edge &e) const {
					return w < e.w;
				}
		};
		
		int n, m;
		vector<vector<pair<int, int>>> adjList;
		vector<Edge> edges;

	public:
		Graph(int n): n(n), adjList(n) {}

		void addEdge(int u, int v, int w) {
			adjList[v].push_back({u, w});
			adjList[u].push_back({v, w});
			edges.push_back({u, v, w});
		}

		vector<int> dijkstra(int s) {
			set<pair<int, int>> pq;

			vector<int> dis(n, INT_MAX);
			vector<int> par(n, -1);
			dis[s] = 0;

			pq.insert({0, s});

			while (!pq.empty()) {
				auto [d, v] = *pq.begin();
				pq.erase(pq.begin());

				if (d != dis[v])
					continue;

				for (auto [u, w] : adjList[v]) {
					if (dis[v] + w < dis[u]) {
						par[u] = v;
						dis[u] = dis[v] + w;
						pq.insert({dis[u], u});
					}
				}
			}

			return dis;
		}
		
		int prim() {
			vector<bool> vis(n, false);

			set<pair<int, int>> pq;
			pq.insert({0, 0});

			int mst = 0;
			while (!pq.empty()) {
				auto [w, v] = *pq.begin();
				pq.erase(pq.begin());

				if (vis[v])
					continue;

				mst += w;
				vis[v] = true;
				for (auto [u, w] : adjList[v]) 
					pq.insert({w, u});
			}

			return mst;
		}

		int kruskal() {
			sort(edges.begin(), edges.end());
			DSU dsu(n);

			int mst = 0;
			for (auto [u, v, w] : edges) {
				if (dsu.join(u, v)) {
					mst += w;
				}
			}

			return mst;
		}
};

int main() {
	Graph g(5);

	g.addEdge(0, 1, 1);
	g.addEdge(0, 2, 6);
	g.addEdge(0, 3, 4);
	g.addEdge(1, 2, 1);
	g.addEdge(1, 4, 2);
	g.addEdge(3, 4, 7);

	cout << g.kruskal() << '\n';

	return 0;
}
