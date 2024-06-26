#include <iostream>
#include <vector> 
#include <map>
#include <cmath>

using namespace std;

typedef long long ll;
using ll = long long;

ll q, n, j, parentJ, leftChildJ, rightChildJ, nextJ, k;
vector<ll> arr(1e3);

// Min heap
int main() {
    cin >> q >> n;
    for (ll numQ = 0; numQ < q; numQ++) {

        for (ll i = 0; i < n; i++) {
            cin >> arr[i];
        }

        // for (ll i = 0; i < n; i++) {
        //     cout << arr[i] << " ";
        // }
        // cout << endl;

        for (ll i = n - 1; i >= 0; i--) {
            j = i;
            while (true) {
                parentJ = floor((j - 1) / 2);

                if (parentJ == 0 && parentJ == j) {
                    break;
                } 
                
                if (arr[parentJ] < arr[j]) {
                    swap(arr[parentJ], arr[j]);
                } else {
                    break;
                }
            }
        }

        k = n - 1;
        while (k >= 0) {
            swap(arr[k], arr[0]);
            k--;

            j = 0;
            while (j <= k) {
                leftChildJ = j * 2 + 1;
                rightChildJ = j * 2 + 2;

                nextJ = leftChildJ;
                if (nextJ > k) {
                    break;
                }

                if (arr[leftChildJ] < arr[rightChildJ]) {
                    nextJ = rightChildJ;
                }

                if (nextJ > k) {
                    break;
                }

                if (arr[nextJ] > arr[j]) {
                    swap(arr[nextJ], arr[j]);
                } else {
                    break;
                }

                j = nextJ;
            }
        }

        swap(arr[0], arr[1]);

        for (ll i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    return 0;
}