#include <iostream>
#include <bitset>

using namespace std;

const uint32_t N = 34;

int sequence[N] = {};
// 0=free, 1=used
bitset<N> bset;

uint32_t P_len = 0;
uint32_t P[N] = {4, 9, 16, 25, 36, 49};

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
        if (next <= 0 || next > N || bset.test(next-1)) continue;

        sequence[i] = next;
        bset.set(next-1, true);
        backtrack(i+1);
        bset.set(next-1, false);
    }

    // there's nothing left to do
}

int main() {
    // calculate the perfect squares
    uint32_t p = 0;
    while (p <= 2*N-1)  {
        p = (P_len+2)*(P_len+2);
        P[P_len] = p; // skips 0*0 and 1*1
        P_len++;
    }

    P_len--;

    for (int i = 0; i < N; i++) {
        sequence[0] = i+1;
        bset.set(i, true);
        backtrack(1);
        bset.set(i, false);
    }
}