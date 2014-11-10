#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int NOT_EXIST = 32767;

int main()
{
#ifndef ONLINE_JUDGE
	ifstream in("in.txt");
	streambuf *cinbuf = cin.rdbuf(); //save old buf
	cin.rdbuf(in.rdbuf());           //redirect std::cin to in.txt!
	ofstream out("out.txt");
	streambuf *coutbuf = cout.rdbuf(); //save old buf
	cout.rdbuf(out.rdbuf());           //redirect std::cout to out.txt!
#endif

	int n;
	cin >> n;

	vector<vector<int>> g(n);
	for (int i = 0; i < n; ++i)
		g[i] = vector<int>(n);
	vector<vector<int>> t(n);
	for (int i = 0; i < n; ++i)
		t[i] = vector<int>();

	for (int i = 0; i < n; ++i)
	for (int j = 0; j < n; ++j)
	{
		cin >> g[i][j];
	}
	int sum = 0;

	// алгоритм
	vector<bool> used(n);
	vector<int> min_e(n, NOT_EXIST), sel_e(n, -1);
	min_e[0] = 0;
	for (int i = 0; i < n; ++i) {
		int v = -1;
		for (int j = 0; j < n; ++j)
		if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
			v = j;
		if (min_e[v] == NOT_EXIST) {
			cout << "No MST!";
			exit(0);
		}

		used[v] = true;
		if (sel_e[v] != -1)
		{
			t[v].push_back(sel_e[v]);
			t[sel_e[v]].push_back(v);
			sum += g[v][sel_e[v]];
		}

		for (int to = 0; to < n; ++to)
		if (g[v][to] < min_e[to]) {
			min_e[to] = g[v][to];
			sel_e[to] = v;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		sort(t[i].begin(), t[i].end());
		for (int j = 0; j < t[i].size(); ++j)
			cout << t[i][j] + 1 << " ";
		cout << "0\n";
	}

	cout << sum;
	return 0;
}