#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<map>
using namespace std;

int N, M;
bool t;
vector<vector<bool>> a;
pair<int, int> start, finish;

vector<pair<int, int>> neighbors(pair<int, int> p) {
	// Vector of pair<int, int>s, which are neighbors of pair<int, int> p 
	vector<pair<int, int>> result;
	pair<int, int> tmp;

	tmp.first = p.first;
	if (p.second - 1 >= 0 && a[p.first][p.second - 1] == 0) {
		tmp.second = p.second - 1;
		result.push_back(tmp);
	}
	if (p.second + 1 < M && a[p.first][p.second + 1] == 0) {
		tmp.second = p.second + 1;
		result.push_back(tmp);
	}
	tmp.second = p.second;
	if (p.first - 1 >= 0 && a[p.first - 1][p.second] == 0) {
		tmp.first = p.first - 1;
		result.push_back(tmp);
	}
	if (p.first + 1 < N && a[p.first + 1][p.second] == 0) {
		tmp.first = p.first + 1;
		result.push_back(tmp);
	}
	return result;
}

int main()
{
	ifstream fin("in.txt");
	ofstream fout("out.txt");

	fin >> N >> M;
	for (int i = 0; i < N; i++) {
		a.push_back(vector<bool>());
		for (int j = 0; j < M; j++) {
			fin >> t;
			a[i].push_back(t);
		}
	}
	fin >> start.first >> start.second >>
		finish.first >> finish.second;
	start.first--; start.second--;
	finish.first--; finish.second--;

	// Start position is incorrect
	if (a[start.first][start.second] == 1) {
		fout << "N";
		return 0;
	}
	// Start position is the same with finish
	if (start.first == finish.first && start.second == finish.second) {
		fout << "Y" << "\n" <<
			start.first << " " << finish.first << "\n" <<
			start.second << " " << finish.second;
		return 0;
	}

	// BFS
	queue<pair<int, int>> q;
	map<pair<int, int>, bool> used;
	for (int i = 0; i < N; i++)
	for (int j = 0; j < M; j++)
		used[pair<int, int>(i, j)] = 0;
	map<pair<int, int>, pair<int, int>> parent;
	pair<int, int> root(-1, -1);

	used[start] = 1;
	q.push(start);
	parent[start] = root;

	while (!q.empty())
	{
		pair<int, int> u = q.front();
		q.pop();
		used[u] = 1;
		for (pair<int, int> v : neighbors(u)) {
			if (!used[v]) {
				used[v] = 1;
				q.push(v);
				parent[v] = u;
			}
		}
	}

	if (!used[finish])
		fout << "N";
	else {
		vector<pair<int, int>> path;
		for (pair<int, int> v = finish; v != root; v = parent[v])
			path.push_back(v);
		reverse(path.begin(), path.end());
		fout << "Y\n";
		for (size_t i = 0; i < path.size(); ++i)
			fout << path[i].first + 1 << " " << path[i].second + 1 << "\n";
	}

	return 0;
}