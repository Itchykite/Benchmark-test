#!/bin/bash
set -e

SRC_DIR="src"
BUILD_DIR="build"
OUT_DIR="out"

mkdir -p "$BUILD_DIR"
mkdir -p "$OUT_DIR"

echo "🧪 Kompilacja C++..."

g++ -O3 -std=c++17 "$SRC_DIR/pure_cpp.cpp" -o "$BUILD_DIR/cpp"
g++ -O3 -std=c++17 "$SRC_DIR/pure_cpp_mt.cpp" -pthread -o "$BUILD_DIR/cpp_mt"
g++ -O3 -std=c++17 -mavx2 "$SRC_DIR/simd_cpp.cpp" -o "$BUILD_DIR/simd"
g++ -O3 -std=c++17 -mavx2 "$SRC_DIR/simd_cpp_mt.cpp" -pthread -o "$BUILD_DIR/simd_mt"
g++ -O3 -std=c++17 -mavx2 -mfma "$SRC_DIR/simd_cpp_fma.cpp" -o "$BUILD_DIR/simd_fma"
g++ -O3 -std=c++17 -mavx2 -mfma "$SRC_DIR/simd_cpp_fma_mt.cpp" -pthread -o "$BUILD_DIR/simd_fma_mt"

echo "version,time_ms" > "$OUT_DIR/results.csv"

echo "🐍 Python..."
python3 "$SRC_DIR/pure_python.py" >> "$OUT_DIR/results.csv"
python3 "$SRC_DIR/numpy_python.py" >> "$OUT_DIR/results.csv"
python3 "$SRC_DIR/pure_python_mt.py" >> "$OUT_DIR/results.csv"
python3 "$SRC_DIR/numpy_python_mt.py" >> "$OUT_DIR/results.csv"

echo "⚙️  C++..."
"$BUILD_DIR/cpp" >> "$OUT_DIR/results.csv"
"$BUILD_DIR/cpp_mt" >> "$OUT_DIR/results.csv"

echo "🚀 SIMD..."
"$BUILD_DIR/simd" >> "$OUT_DIR/results.csv"
"$BUILD_DIR/simd_mt" >> "$OUT_DIR/results.csv"
"$BUILD_DIR/simd_fma" >> "$OUT_DIR/results.csv"
"$BUILD_DIR/simd_fma_mt" >> "$OUT_DIR/results.csv"

echo ""

