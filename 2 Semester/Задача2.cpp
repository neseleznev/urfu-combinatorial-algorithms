#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10000;
int n;
vector<int> g[MAXN];
int match[MAXN], p[MAXN], base[MAXN], q[MAXN];
bool used[MAXN], blossom[MAXN];

int lca(int a, int b) {
    bool used[MAXN] = { 0 };
    for (;;) {
        a = base[a];
        used[a] = true;
        if (match[a] == -1)  break;
        a = p[match[a]];
    }
    for (;;) {
        b = base[b];
        if (used[b])  return b;
        b = p[match[b]];
    }
}

void mark_path(int v, int b, int children) {
    while (base[v] != b) {
        blossom[base[v]] = blossom[base[match[v]]] = true;
        p[v] = children;
        children = match[v];
        v = p[match[v]];
    }
}

int find_path(int root) {
    fill(used, used + MAXN, 0);
    fill(p, p + MAXN, -1);
    for (int i = 0; i<n; ++i)
        base[i] = i;

    used[root] = true;
    int qh = 0, qt = 0;
    q[qt++] = root;
    while (qh < qt) {
        int v = q[qh++];
        for (size_t i = 0; i<g[v].size(); ++i) {
            int to = g[v][i];
            if (base[v] == base[to] || match[v] == to)  continue;
            if (to == root || match[to] != -1 && p[match[to]] != -1) {
                int curbase = lca(v, to);
                fill(blossom, blossom + MAXN, 0);
                for (int i = 0; i < MAXN; i++)
                    blossom[i] = 0;
                mark_path(v, curbase, to);
                mark_path(to, curbase, v);
                for (int i = 0; i<n; ++i)
                if (blossom[base[i]]) {
                    base[i] = curbase;
                    if (!used[i]) {
                        used[i] = true;
                        q[qt++] = i;
                    }
                }
            }
            else if (p[to] == -1) {
                p[to] = v;
                if (match[to] == -1)
                    return to;
                to = match[to];
                used[to] = true;
                q[qt++] = to;
            }
        }
    }
    return -1;
}

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

    int k, l, tmp, a, b;
    cin >> k >> l;
    n = k + l;

    for (int i = 0; i < k; ++i)
    for (int j = 0; j < l; ++j)
    {
        cin >> tmp;
        if (tmp)
        {
            g[i].push_back(k + j);
            g[k + j].push_back(i);
        }
    }

    fill(match, match + MAXN, -1);
    for (int i = 0; i < n; ++i)
    if (match[i] == -1) {
        int v = find_path(i);
        while (v != -1) {
            int pv = p[v], ppv = match[pv];
            match[v] = pv, match[pv] = v;
            v = ppv;
        }
    }

    int cnt = 0, temp, ans[MAXN + 1];
    fill(ans, ans + MAXN + 1, -1);
    for (int i = 0; i < MAXN; i++) {
        if (match[i] != -1) {
            cnt++;
            a = match[i] + 1; b = match[match[i]] + 1;
            if (a > b) { temp = a; a = b; b = temp; }
            ans[a] = b;
        }
    }

    for (int i = 1; i <= k; i++)
    {
        if (ans[i] != -1)
            cout << ans[i] << " ";
        else
            cout << "0 ";
    }
    return 0;
}