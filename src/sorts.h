#pragma once
#include <bits/stdc++.h>
using namespace std;

// ---------- QuickSort (median-of-three, Hoare-style, de quy vao nua nho hon) ----------
static void insertion(double* a, long l, long r) {
    for (long i = l + 1; i <= r; i++) {
        double v = a[i]; long j = i - 1;
        while (j >= l && a[j] > v) { a[j + 1] = a[j]; j--; }
        a[j + 1] = v;
    }
}
static void quick_rec(double* a, long l, long r) {
    while (r - l > 16) {
        long m = l + (r - l) / 2;
        if (a[m] < a[l]) swap(a[m], a[l]);
        if (a[r] < a[l]) swap(a[r], a[l]);
        if (a[r] < a[m]) swap(a[r], a[m]);
        double p = a[m];
        long i = l, j = r;
        while (i <= j) {
            while (a[i] < p) i++;
            while (a[j] > p) j--;
            if (i <= j) { swap(a[i], a[j]); i++; j--; }
        }
        // de quy nua nho hon, lap nua lon -> do sau stack O(log n)
        if (j - l < r - i) { quick_rec(a, l, j); l = i; }
        else               { quick_rec(a, i, r); r = j; }
    }
    insertion(a, l, r);
}
void quick_sort(vector<double>& a) { if (a.size() > 1) quick_rec(a.data(), 0, (long)a.size() - 1); }

// ---------- HeapSort (max-heap, tu cai dat) ----------
static void sift_down(double* a, long n, long i) {
    double v = a[i];
    while (true) {
        long c = 2 * i + 1;
        if (c >= n) break;
        if (c + 1 < n && a[c + 1] > a[c]) c++;
        if (a[c] <= v) break;
        a[i] = a[c]; i = c;
    }
    a[i] = v;
}
void heap_sort(vector<double>& v) {
    long n = v.size(); double* a = v.data();
    for (long i = n / 2 - 1; i >= 0; i--) sift_down(a, n, i);
    for (long e = n - 1; e > 0; e--) { swap(a[0], a[e]); sift_down(a, e, 0); }
}

// ---------- MergeSort (top-down, dung 1 mang phu) ----------
static void merge_rec(double* a, double* t, long l, long r) {
    if (r - l <= 16) { insertion(a, l, r - 1); return; }
    long m = l + (r - l) / 2;
    merge_rec(a, t, l, m); merge_rec(a, t, m, r);
    if (!(a[m] < a[m - 1])) return;               // da co thu tu
    copy(a + l, a + m, t + l);
    long i = l, j = m, k = l;
    while (i < m && j < r) a[k++] = (a[j] < t[i]) ? a[j++] : t[i++];
    while (i < m) a[k++] = t[i++];
}
void merge_sort(vector<double>& v) {
    vector<double> t(v.size());
    if (v.size() > 1) merge_rec(v.data(), t.data(), 0, (long)v.size());
}

// ---------- std::sort ----------
void std_sort(vector<double>& v) { sort(v.begin(), v.end()); }
