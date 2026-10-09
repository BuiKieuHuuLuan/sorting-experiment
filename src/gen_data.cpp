// Sinh 10 day du lieu, moi day N so thuc (double).
// Day 1: tang dan; Day 2: giam dan; Day 3..10: ngau nhien.
// Ghi ra data/dataK.bin (nhi phan double, little-endian) - seed co dinh de tai lap.
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char** argv) {
    size_t N = argc > 1 ? stoull(argv[1]) : 1000000;
    string dir = argc > 2 ? argv[2] : "data";
    mt19937_64 rng(20261001);
    uniform_real_distribution<double> dist(-1e6, 1e6);
    for (int k = 1; k <= 10; k++) {
        vector<double> a(N);
        for (auto& x : a) x = dist(rng);
        if (k == 1) sort(a.begin(), a.end());
        if (k == 2) sort(a.begin(), a.end(), greater<double>());
        string fn = dir + "/data" + to_string(k) + ".bin";
        FILE* f = fopen(fn.c_str(), "wb");
        fwrite(a.data(), sizeof(double), N, f);
        fclose(f);
        printf("Wrote %s (%zu doubles)\n", fn.c_str(), N);
    }
}
