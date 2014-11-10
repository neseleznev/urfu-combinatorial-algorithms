#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");
int N, t;
vector<vector<int>> g;
vector<bool> used;
vector<int> color;
bool _terminate = false;

void dfs(int u)
{
	if (_terminate)
		return;
	used[u] = 1;
	for (size_t i = 0; i < g[u].size(); ++i)
	{
		int v = g[u][i];
		if (used[v])
		{
			if (color[u] == color[v]) {
				_terminate = true;
				return;
			}
		}
		else
		{
			color[v] = (color[u]+1) % 2;
			dfs(v);
		}
	}
}

void print_color(bool c)
{
	for (size_t i = 0; i < color.size(); ++i)
		if (color[i] == (int)c)
			fout << i+1 << " ";
}

int main()
{
	fin >> N;

	for (int i = 0; i < N; i++)
	{
		g.push_back(vector<int>());
		used.push_back(0);
		color.push_back(0);
		while (fin >> t && t != 0)
			g[i].push_back(t - 1);
	}


	for (int i = 0; i < N; i++)
	{
		if (!used[i]) {
			dfs(i);
			if (_terminate) {
				fout << "N";
				return 0;
			}
		}
	}
	bool first_color = (bool)color[0];
	fout << "Y\n";
	print_color(first_color);
	fout << "0\n";
	print_color(!first_color);

	return 0;
}