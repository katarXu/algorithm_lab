#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <time.h>

using namespace std;

#define N 30000
#define M 60000
#define INF 0x3f3f3f3f

typedef pair<long long, int> dat;

int head[N], cnt = 0;
long long h[N];

struct Edge{
	int next = 0, to = 0, weight = 0;
} edge[M];

void printWay(int s, int t, int father[], ostream& out){
	if (s != t) {
		printWay(s, father[t], father, out);
		out << "," << t;
	}
	else
		out << "(" << t;
}

void func(int n) {
	queue<int> q;
	bool visited[N];
	int sum[N];
	memset(h, 0x3f, sizeof(h));
	memset(visited, 0, sizeof(visited));
	h[0] = 0, visited[0] = true;
	q.push(0);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (++sum[u] >= n) 
			exit(0);
		visited[u] = false;
		for (int i = head[u]; i; i = edge[i].next) {
			int v = edge[i].to, w = edge[i].weight;
			if (h[v] > h[u] + w) {
				h[v] = h[u] + w;
				if (!visited[v]) {
					q.push(v);
					visited[v] = true;
				}
			}
		}
	}
}
void dijkstra(int n, int s, ostream& out){
	bool visited[N];
	int father[N];
	long long dist[N];
	priority_queue<dat> q;
	memset(visited, false, sizeof(visited));
	dist[s] = 0;
	q.push(make_pair(0, s));

	for (int i = 1; i <= n; i++)
		dist[i] = INF;
	while (!q.empty()){
		int u = q.top().second;
		q.pop();
		if (visited[u])
			continue;
		visited[u] = true;
		for (int i = head[u]; i; i = edge[i].next){
			int v = edge[i].to, w = edge[i].weight;
			if (dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
				father[v] = u;
				if (!visited[v])
					q.push(make_pair(-dist[v], v));
			}
		}
	}
	for (int i = 1; i <= n; i++){
		if (i == s)
			continue;
		if (dist[i] == INF)
			out << "There is no way from " << s << " to " << i << endl;
		else{
			out << s << " to " << i << "\tw : " << dist[i] << endl;
			printWay(s, i, father, out);
			out << ")" << endl;
		}
	}
	return;
}

void add(int u, int v, int w) {
	edge[++cnt].next = head[u];
	edge[cnt].to = v, edge[cnt].weight = w;
	head[u] = cnt;
	return;
}

int rand(int n) {
	return n ? rand() % n : 0;
}

double test(int n, int lo, ostream& in, ostream& out){
	int m = (int)(log(n) / log(lo));
	for (int j = 1; j <= n; j++)
		for (int i = 1; i <= m; i++){
			int k = rand(n) + 1;
			int w = rand(50) + 1;
			add(j, k, w);
			in << "(" << j << " , " << k << ") " << w << endl;
		}

	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);

	for (int i = 1; i <= n; i++)
		add(0, i, 0);
	func(n);
	for (int i = 1; i <= n; i++)
		for (int j = head[i]; j; j = edge[j].next)
			edge[j].weight += h[i] - h[edge[j].to];
	for (int i = 1; i <= n; i++)
		dijkstra(n, i, out);

	QueryPerformanceCounter(&t2);
	return (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart;
}

