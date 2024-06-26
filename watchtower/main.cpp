#include <iostream>
#include <vector> 
#include <map>

using namespace std;

typedef long long ll;
using ll = long long;


typedef unsigned int ui;
using ui = unsigned int;

ll q, qCode, x, y, dist, towerId, n;
ll MAX_N = 1000;
vector<vector<vector<ui>>> trees(MAX_N, vector<vector<ui>>(4 * MAX_N, vector<ui>(6, 0)));

class Solution {
    public:
        ll n;

        Solution(
            ll n
        ) {
            this->n = n;
        }

        void buildTower(ll x, ll y, ll towerId) {
            updateTree(trees[x], 0, n - 1, 0, y, towerId, 1);
        }

        void updateTree(vector<vector<ui>> &tree, ll left, ll right, ll treeIndex, ll valueIndex, ll towerId, ui value) {
            if (left == right && valueIndex == left) {
                if (towerId == 0) {
                    for (int i = 0; i < 6; i++) {
                        tree[treeIndex][i] = value;
                    }
                } else {
                    tree[treeIndex][towerId] = value;
                }

                tree[treeIndex][towerId] = value;
                return;
            }

            int mid = (left + right) / 2;
            int leftTreeIndex = 2 * treeIndex + 1;
            int rightTreeIndex = 2 * treeIndex + 2;

            if (left <= valueIndex && valueIndex <= mid) {
                updateTree(tree, left, mid, leftTreeIndex, valueIndex, towerId, value);
            } else {
                updateTree(tree, mid + 1, right, rightTreeIndex, valueIndex, towerId, value);
            }

            if (towerId == 0) {
                for (int i = 0; i < 6; i++) {
                    tree[treeIndex][i] = tree[leftTreeIndex][i] + tree[rightTreeIndex][i];
                }

            } else {
                tree[treeIndex][towerId] = tree[leftTreeIndex][towerId] + tree[rightTreeIndex][towerId];
            }
            return;
        }

        void removeTower(ll x, ll y) {
            updateTree(trees[x], 0, n - 1, 0, y, 0, 0);
        }

        
        ll getRange(vector<vector<ui>> &tree, ll left, ll right, ll treeIndex, ll targetLeft, ll targetRight, ll towerId) {
            ll value = 0;
            if (left == targetLeft && right == targetRight) {
                if (towerId == 0) {
                    for (ui count: tree[treeIndex]) {
                        value += count;
                    }
                } else {
                    value += tree[treeIndex][towerId];
                }

                return value;
            }

            ll mid = (left + right) / 2;
            int leftTreeIndex = 2 * treeIndex + 1;
            int rightTreeIndex = 2 * treeIndex + 2;

            if (targetLeft <= mid) {
                value += getRange(tree, left, mid, leftTreeIndex, targetLeft, min(mid, targetRight), towerId);
            }

            if (mid < targetRight) {
                value += getRange(tree, mid + 1, right, rightTreeIndex, max(mid + 1, targetLeft), targetRight, towerId);
            }

            return value;
        }

        ll countTowers(ll x, ll y, ll dist, ll towerId) {
            ll totalCount = 0;
            ll minIndexX = max(x - dist, (ll) 0);
            ll maxIndexX = min(x + dist, n - 1);
            ll minIndexY = max(y - dist, (ll) 0);
            ll maxIndexY = min(y + dist, n - 1);
            for (int rowIndex = minIndexX; rowIndex <= maxIndexX; rowIndex++) {
                totalCount += getRange(trees[rowIndex], 0, n - 1, 0, minIndexY, maxIndexY, towerId);
            }

            return totalCount;
        }

        ll getClosest(ll x, ll y, ll towerId) {
            return 0;
        }
};

Solution* solution = nullptr;

int main() {
    cin >> q;
    
    for (int i = 0; i < q; i++) {
        cin >> qCode;

        if (qCode == 1) {
            cin >> n;
            solution = new Solution(n);
        } else if (qCode == 2) {
            cin >> x >> y >> towerId;
            solution->buildTower(x, y, towerId);
        } else if (qCode == 3) {
            cin >> x >> y;
            solution->removeTower(x, y);
        } else if (qCode == 4) {
            cin >> x >> y >> dist >> towerId;
            printf("%lli\n", solution->countTowers(x, y, dist, towerId));
        } else if (qCode == 5) {
            cin >> x >> y >> towerId;
            printf("%lli\n", solution->getClosest(x, y, towerId));
        }
    }
    return 0;
}