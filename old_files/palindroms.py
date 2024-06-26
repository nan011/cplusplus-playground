MOD = int(1e9) + 7

def generate_combination(memo, strings, string_index, index, word, chosen_count):
    n = len(strings[string_index])

    if index >= n:
        return 0

    possible_count = generate_combination(
        memo,
        strings,
        string_index,
        index + 1,
        word ^ (1 << (ord(strings[string_index][index]) - ord('a'))),
        chosen_count + 1
    ) % MOD

    possible_count += generate_combination(
        memo,
        strings,
        string_index,
        index + 1,
        word,
        chosen_count
    ) % MOD

    if chosen_count > 0:
        possible_count += evaluate(
            memo,
            strings,
            string_index + 1,
            word
        ) % MOD

    return possible_count % MOD

def is_palindrome(word):
    bit_count = 0
    while word != 0:
        if (word & 1) == 1:
            bit_count += 1

        if bit_count > 1:
            return False

        word = word >> 1

    return True

def evaluate(memo, strings, string_index, word):
    n = len(strings)
    if string_index >= n:
        print(word)
        return 1 if is_palindrome(word) else 0

    if memo[string_index][word] != -1:
        return memo[string_index][word]

    memo[string_index][word] = generate_combination(
        memo,
        strings,
        string_index,
        0,
        word,
        0
    ) % MOD
    return memo[string_index][word]

def palindromic_strings(strings):
    n = len(strings)
    memo = [[-1 for _ in range(2 ** 26 + 1)] for _ in range(n)]
    return evaluate(memo, strings, 0, 0)

if __name__ == "__main__":
    q = int(input())
    for _ in range(q):
        n = int(input())
        A = [input() for _ in range(n)]
        result = palindromic_strings(A)
        print(result)