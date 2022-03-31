#include <iostream>

using namespace std;

const uint32_t N = 43;

int sequence[N] = {};
// 0=free, 1=used
uint64_t bitset = 0;

const int P[] = {4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144};
const int get_P_len() {
    for (int i = 0; i < sizeof(P); i++) {
        if (P[i] > 2*N-1) return i;
    }

    return 0;
}

uint32_t P_len = get_P_len();

void backtrack(int i) {
    if (i == N) {
        // we made it 
        for (int i = 0; i < N; i++) cout << sequence[i] << ' ';
        cout <<'\n';
        return;
    }

    for (int j = 0; j < P_len; j++) {
        int next = P[j]-sequence[i-1];
        // next is taken
        if (next <= 0 || next > N || bitset & ((uint64_t)1 << (next-1))) continue;

        sequence[i] = next;
        bitset |= ((uint64_t)1 << (next-1));
        backtrack(i+1);
        bitset &= ~((uint64_t)1 << (next-1));
    }

    // there's nothing left to do
}

int main() {
    for (int i = 0; i < N; i++) {
        sequence[0] = i+1;
        bitset |= ((uint64_t)1 << i);
        backtrack(1);
        bitset &= ~((uint64_t)1 << i);
    }
}