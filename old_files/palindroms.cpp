#include <bits/stdc++.h>

using namespace std;

int evaluate(
    vector<vector<int>>& memo,
    vector<string>& strings,
    int stringIndex,
    int word
);

/*
 * Complete the 'palindromicStrings' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING_ARRAY a as parameter.
 */
const int MOD = 1e9 + 7;


int generateCombination(
    vector<vector<int>>& memo,
    vector<string>& strings,
    int stringIndex,
    int index,
    int word,
    int chosenCount
) {
    int n = strings[stringIndex].size();

    if (index >= n) {
        return 0;
    }

    int possibleCount = generateCombination(
        memo,
        strings,
        stringIndex,
        index + 1,
        word ^ (1 << strings[stringIndex][index] - 'a'),
        chosenCount + 1
    );
    possibleCount %= MOD;

    possibleCount += generateCombination(
        memo,
        strings,
        stringIndex,
        index + 1,
        word,
        chosenCount
    );
    possibleCount %= MOD;

    if (chosenCount > 0) {
        possibleCount += evaluate(
            memo,
            strings,
            stringIndex + 1,
            word
        );
        possibleCount %= MOD;

    }

    return possibleCount % MOD;
}

bool isPalindrome(int word) {
    int bitCount = 0;
    while (word != 0) {
        if ((word & 1) == 1) {
            bitCount += 1;
        }

        if (bitCount > 1) {
            return false;
        }

        word = word >> 1;
    }

    return true;
}

int evaluate(
    vector<vector<int>>& memo,
    vector<string>& strings,
    int stringIndex,
    int word
) {
    int n = strings.size();
    if (stringIndex >= n) {
        if (isPalindrome(word)) {
            return 1;
        }

        return 0;
    }

    if (memo[stringIndex][word] != -1) {
        return memo[stringIndex][word];
    } 

    memo[stringIndex][word] = generateCombination(
        memo,
        strings,
        stringIndex,
        0,
        word,
        0
    );
    memo[stringIndex][word] %= MOD;
    return memo[stringIndex][word];
}

int palindromicStrings(vector<string> strings) {
    int n = strings.size();
    vector<vector<int>> memo(n, vector<int>(pow(2, 26) + 1, -1));
    printf("test\n");
    // return evaluate(memo, strings, 0, 0);
    return 1;
}


int main()
{
    int q, n, result;

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> n;
        vector<string> A(n);
        for (int j = 0; j < n; j++) {
            cin >> A[j];
        }

        result = palindromicStrings(A);

        cout << result << endl;
    }

    return 0;
}
