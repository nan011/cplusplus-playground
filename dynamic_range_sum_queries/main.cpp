#include <iostream>
#include <vector> 
#include <map>

typedef long long ll;
using ll = long long;

using namespace std;

ll n, q, x, a, b, c, diff, mi;
vector<ll> values(2 * 1e5);
vector<ll> tree(4 * values.size());


void constructTree(vector<ll> &tree, vector<ll>& values, ll left, ll right, ll treeIndex) {
    if (left == right) {
        tree[treeIndex] = values[left];
        return;
    }
    
    int mid = (left + right) / 2;
    int leftTreeIndex = 2 * treeIndex + 1;
    int rightTreeIndex = 2 * treeIndex + 2;
    constructTree(tree, values, left, mid, leftTreeIndex);
    constructTree(tree, values, mid + 1, right, rightTreeIndex);

    tree[treeIndex] = tree[leftTreeIndex] + tree[rightTreeIndex];
    return;
}

void updateTree(vector<ll> &tree, vector<ll>& values, ll left, ll right, ll treeIndex, ll valueIndex) {
    // printf("%i %i %i %i\n", left, right, treeIndex, valueIndex);

    if (left == right && valueIndex == left) {
        tree[treeIndex] = values[valueIndex];
        return;
    }

    int mid = (left + right) / 2;
    int leftTreeIndex = 2 * treeIndex + 1;
    int rightTreeIndex = 2 * treeIndex + 2;

    if (left <= valueIndex && valueIndex <= mid) {
        updateTree(tree, values, left, mid, leftTreeIndex, valueIndex);
    } else {
        updateTree(tree, values, mid + 1, right, rightTreeIndex, valueIndex);
    }

    tree[treeIndex] = tree[leftTreeIndex] + tree[rightTreeIndex];
    return;
}

ll getRange(vector<ll> &tree, ll left, ll right, ll treeIndex, ll targetLeft, ll targetRight) {
    if (left == targetLeft && right == targetRight) {
        return tree[treeIndex];
    }

    ll mid = (left + right) / 2;
    int leftTreeIndex = 2 * treeIndex + 1;
    int rightTreeIndex = 2 * treeIndex + 2;

    ll value = 0;
    if (targetLeft <= mid) {
        value += getRange(tree, left, mid, leftTreeIndex, targetLeft, min(mid, targetRight));
    }

    if (mid < targetRight) {
        value += getRange(tree, mid + 1, right, rightTreeIndex, max(mid + 1, targetLeft), targetRight);
    }

    return value;
}


int main() {
    cin >> n >> q;
    mi = -1;
    
    for (int i = 0; i < n; i++) {
        cin >> x;
        values[i] = x;
    }
    constructTree(tree, values, 0, n - 1, 0);

    // for (int i = 0; i < 4 * n; i++) {
    //     cout << tree[i] << " ";
    // }
    // cout << endl;

    for (int i = 0; i < q; i++) {
        cin >> a >> b >> c;

        if (a == 1) {
            values[b - 1] = c;
            updateTree(tree, values, 0, n - 1, 0, b - 1);
            // for (int i = 0; i < 4 * n; i++) {
            //     cout << tree[i] << " ";
            // }
            // cout << endl;
        } else {
            cout << getRange(tree, 0, n - 1, 0, b - 1, c - 1) << endl;
        }
    }  

    return 0;
}