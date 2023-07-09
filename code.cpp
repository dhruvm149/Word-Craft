#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

class node
{
public:
  char data;
  map<char, node *> child;
  bool isend;
  string word;

  node(char c)
  {
    data = c;
    isend = false;
    word = "";
  }
};

class trie
{
public:
  node *root;

  trie()
  {
    root = new node('\0');
  }

  void add(string s)
  {
    node *temp = root;
    for (auto i : s)
    {
      if (temp->child.count(i) == 0)
      {
        temp->child[i] = new node(i);
      }
      temp = temp->child[i];
    }
    temp->isend = true;
    temp->word = s;
  }

  void print(node *root, string ans)
  {
    if (root->isend)
    {
      cout << ans + root->data << endl;
    }
    for (auto i : root->child)
    {
      print(i.second, ans + i.first);
    }
  }
};

void dfs(vector<vector<char>> board, node *temp, int i, int j, vector<vector<bool>> used, set<string> &ans)
{
  if (i < 0 || j < 0 || i == board.size() || j == board[0].size())
  {
    return;
  }

  if (temp->data != board[i][j])
  {
    return;
  }

  if (used[i][j])
  {
    return;
  }

  used[i][j] = true;

  if (temp->isend)
  {
    ans.insert(temp->word);
  }

  for (auto k : temp->child)
  {
    dfs(board, k.second, i - 1, j - 1, used, ans);
    dfs(board, k.second, i - 1, j, used, ans);
    dfs(board, k.second, i, j - 1, used, ans);
    dfs(board, k.second, i + 1, j + 1, used, ans);
    dfs(board, k.second, i, j + 1, used, ans);
    dfs(board, k.second, i + 1, j, used, ans);
    dfs(board, k.second, i + 1, j - 1, used, ans);
    dfs(board, k.second, i - 1, j + 1, used, ans);
  }
  used[i][j] = false;
}

void solve()
{

  int n, m;
  cin >> n >> m;
  vector<vector<char>> board(n, vector<char>(m));

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cin >> board[i][j];
    }
  }

  trie t;
  int number_of_words;
  cin >> number_of_words;

  while (number_of_words--)
  {
    string word;
    cin >> word;

    t.add(word);
  }

  vector<vector<bool>> used(n, vector<bool>(m, false));

  set<string> ans;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (t.root->child.count((board[i][j])) != 0)
      {
        dfs(board, t.root->child[board[i][j]], i, j, used, ans);
      }
    }
  }

  for (auto i : ans)
  {
    cout << i << endl;
  }
}

int main()
{
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ll TEST_CASES = 1;
  // cin>>TEST_CASES; //comment for single test case
  while (TEST_CASES--)
  {
    solve();
  }
  return 0;
}