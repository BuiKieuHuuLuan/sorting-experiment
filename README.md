# Sorting experiment (IT003.R17)
QuickSort / HeapSort / MergeSort / std::sort trên 10 dãy × 1.000.000 số thực.

- `src/` – mã nguồn C++ (`gen_data.cpp`, `sorts.h`, `main.cpp`)
- `data/` – 10 file nhị phân `dataK.bin` (double, 8 MB/file); tái tạo bằng `gen_data` (seed 20261001)
- `report/` – báo cáo (`Sorting_Report.pdf`, `.docx`), `results.csv`, `chart.png`

```
g++ -O2 -std=c++17 -o gen src/gen_data.cpp && ./gen 1000000 data
g++ -O2 -std=c++17 -o run src/main.cpp && ./run data report/results.csv
```
