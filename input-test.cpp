// input test
// Link: spoj.com/problems/INTEST/
// Input - The input begins with two positive integers n k.
// The next n lines of input contain one positive integer
// Output - Write a single integer to output, denoting how many integers are divisible by k.
//
// SPOJ Result PASS 0.4 Sec

#include <iostream>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int count, n, k, value = 0;
	std::cin >> n >> k;
	while (std::cin >> value) {
		if (value % k == 0) count++;
	}
	std::cout << count;
	return 0;
}
