// Doc data/dataK.bin, chay tung thuat toan, do thoi gian (ms), ghi results.csv
#include "sorts.h"
using namespace std;
using Clock = chrono::steady_clock;

int main(int argc, char** argv) {
    string dir = argc > 1 ? argv[1] : "data";
    string out = argc > 2 ? argv[2] : "results.csv";
    struct Algo { const char* name; void (*fn)(vector<double>&); };
    Algo algos[] = {{"Quicksort", quick_sort}, {"Heapsort", heap_sort},
                    {"Mergesort", merge_sort}, {"sort (C++)", std_sort}};
    FILE* fo = fopen(out.c_str(), "w");
    fprintf(fo, "data,Quicksort,Heapsort,Mergesort,sort (C++)\n");
    for (int k = 1; k <= 10; k++) {
        string fn = dir + "/data" + to_string(k) + ".bin";
        FILE* f = fopen(fn.c_str(), "rb");
        if (!f) { fprintf(stderr, "Cannot open %s\n", fn.c_str()); return 1; }
        fseek(f, 0, SEEK_END); size_t n = ftell(f) / sizeof(double); fseek(f, 0, SEEK_SET);
        vector<double> orig(n);
        if (fread(orig.data(), sizeof(double), n, f) != n) return 1;
        fclose(f);
        vector<double> ref = orig; sort(ref.begin(), ref.end());   // dung de kiem tra dung/sai
        fprintf(fo, "%d", k);
        printf("Data %d (n=%zu):", k, n);
        for (auto& al : algos) {
            vector<double> a = orig;                 // sao chep, khong tinh vao thoi gian
            auto t0 = Clock::now();
            al.fn(a);
            auto t1 = Clock::now();
            double ms = chrono::duration<double, milli>(t1 - t0).count();
            if (a != ref) { fprintf(stderr, "\n%s SAI tren data %d\n", al.name, k); return 2; }
            fprintf(fo, ",%.3f", ms);
            printf("  %s=%.2f ms", al.name, ms);
        }
        fprintf(fo, "\n"); printf("\n");
    }
    fclose(fo);
}
