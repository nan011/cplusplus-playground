#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
long evaluateRight(
    vector<unordered_map<string, long>>& memo,
    vector<string>& strings,
    int stringIndex,
    string rightSubString
);
long evaluateLeft(
    vector<unordered_map<string, long>>& memo,
    vector<string>& strings,
    int stringIndex,
    string rightSubString
);

/*
 * Complete the 'palindromicStrings' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING_ARRAY a as parameter.
 */
const int MOD = 1e9 + 7;

// bool isPalindrome(string word) {
//     int n = word.size();

//     int maxIteration = ceil((float) n / 2);
//     for (int index = 0; index < maxIteration; index++) {
//         if (word[index] != word[(n - 1) - index]) {
//             return false;
//         }
//     }

//     return true;
// }

long evaluateRightSequence(
    vector<unordered_map<string, long>>& memo,
    vector<string>& strings,
    int stringIndex,
    string rightSubString,
    int rightSubStringIndex
) {
    if (rightSubString.size() == 0 || rightSubStringIndex >= (int) strings[stringIndex].size()) {
        return 0;
    }

    long possibleCount = 0;
    if (rightSubString[0] == strings[stringIndex][rightSubStringIndex]) {
        string newRightSubString = rightSubString.substr(1, rightSubString.size() - 1);
        possibleCount += evaluateRight(
            memo,
            strings,
            stringIndex + 1,
            newRightSubString
        );
        possibleCount %= MOD;

        possibleCount += evaluateRightSequence(
            memo,
            strings,
            stringIndex,
            newRightSubString,
            rightSubStringIndex + 1
        );

        possibleCount %= MOD;
    }

    possibleCount += evaluateRightSequence(
        memo,
        strings,
        stringIndex,
        rightSubString,
        rightSubStringIndex + 1
    );
    possibleCount %= MOD;

    return possibleCount;
}

long evaluateRight(
    vector<unordered_map<string, long>>& memo,
    vector<string>& strings,
    int stringIndex,
    string rightSubString
) {
    // printf("[P1] %d %s\n", stringIndex, rightSubString.c_str());
    if (memo[stringIndex].find(rightSubString) != memo[stringIndex].end()) {
        return memo[stringIndex][rightSubString];
    }

    int n = strings.size();

    if (stringIndex == n && rightSubString.size() == 0) {
        // printf("[E] %d %s\n", stringIndex, rightSubString.c_str());
        memo[stringIndex][rightSubString] = 1;
        return memo[stringIndex][rightSubString];
    }

    long possibleCount = evaluateRightSequence(
        memo,
        strings,
        stringIndex,
        rightSubString,
        0
    );
    possibleCount %= MOD;


    // printf("[P2] %d %s : %d\n", stringIndex, rightSubString.c_str(), possibleCount);
    memo[stringIndex][rightSubString] = possibleCount;
    return memo[stringIndex][rightSubString];

}

long evaluateLeftSequence(
    vector<unordered_map<string, long>>& memo,
    vector<string>& strings,
    int stringIndex,
    string rightSubString,
    int rightSubStringIndex
) {
    if (rightSubStringIndex >= (int) strings[stringIndex].size()) {
        return 0;
    }

    long possibleCount = 0;

    string newRightSubString = strings[stringIndex][rightSubStringIndex] + rightSubString;
    possibleCount += evaluateLeft(
        memo,
        strings,
        stringIndex + 1,
        newRightSubString
    );
    possibleCount %= MOD;

    possibleCount += evaluateLeftSequence(
        memo,
        strings,
        stringIndex,
        newRightSubString,
        rightSubStringIndex + 1
    );

    possibleCount %= MOD;

    possibleCount += evaluateLeftSequence(
        memo,
        strings,
        stringIndex,
        rightSubString,
        rightSubStringIndex + 1
    );
    possibleCount %= MOD;

    return possibleCount;
}

long evaluateLeft(
    vector<unordered_map<string, long>>& memo,
    vector<string>& strings,
    int stringIndex,
    string rightSubString
) {
    if (stringIndex >= (int) strings.size()) {
        return 0;
    }

    long possibleCount = evaluateLeftSequence(
        memo,
        strings,
        stringIndex,
        rightSubString,
        0
    );
    possibleCount %= MOD;

    printf("%s %d", rightSubString.c_str(), rightSubString.size() > 0);

    if (rightSubString.size() > 0) {
        possibleCount += evaluateRight(
            memo,
            strings,
            stringIndex,
            rightSubString
        );
        possibleCount %= MOD;

        // Ignore the middle
        if (rightSubString.size() > 1 && rightSubString.size() % 2 == 1) {
            possibleCount += evaluateRight(
                memo,
                strings,
                stringIndex,
                rightSubString.substr(1, rightSubString.size() - 1)
            );
            possibleCount %= MOD;
        }
    }

    return possibleCount % MOD;
}

long palindromicStrings(vector<string> strings) {
    vector<unordered_map<string, long>> memo;

    for (int index = 0; index < (int) strings.size(); index++) {
        memo.push_back({});
    }

    // cout << "test";

    return evaluateLeft(memo, strings, 0, "");
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a_count_temp;
        getline(cin, a_count_temp);

        int a_count = stoi(ltrim(rtrim(a_count_temp)));

        vector<string> a(a_count);

        for (int i = 0; i < a_count; i++) {
            string a_item;
            getline(cin, a_item);

            a[i] = a_item;
        }

        int result = palindromicStrings(a);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
