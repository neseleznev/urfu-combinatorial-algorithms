#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

const int INF = 1000000000;
const int EDGE_DOENS_NOT_EXIST = 32767;

int main()
{
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	int N, start, end;

	fin >> N;
	int ** a = new int*[N];

	for (int i = 0; i < N; i++) {
		a[i] = new int[N];
		for (int j = 0; j < N; j++) {
			fin >> a[i][j];
		}
	}
	fin >> start >> end;
	start--; end--;

	vector<int> d(N, INF), parent(N, -1);
	d[start] = 0;
	vector<char> used(N);

	for (int i = 0; i < N; ++i)
	{
		int v = -1;
		for (int j = 0; j < N; ++j)
			if (!used[j] && (v == -1 || d[j] < d[v]))
				v = j;
		if (d[v] == INF)
			break;
		used[v] = true;

		for (int j = 0; j < N; ++j)
		if (a[v][j] != EDGE_DOENS_NOT_EXIST) {
			int to = j,
				len = a[i][j];
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				parent[to] = v;
			}
		}
	}

	if (!used[end])
		fout << "N";
	else {
		vector<int> path;
		for (int v = end; v != -1; v = parent[v])
			path.push_back(v);
		reverse(path.begin(), path.end());
		fout << "Y\n";
		for (size_t i = 0; i < path.size(); ++i)
			fout << path[i] + 1 << " ";
		int sum = 0;
		fout << "\n";
		for (size_t i = 0; i < path.size()-1; ++i)
			sum += a[path[i]][path[i+1]];
		fout << sum << "\n";
	}

	return 0;
}