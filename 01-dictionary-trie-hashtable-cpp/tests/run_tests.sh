#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../.." && pwd)"
BIN="$ROOT_DIR/bin/diccionario_aed1"

if [ ! -f "$BIN" ] && [ ! -f "${BIN}.exe" ]; then
    mkdir -p "$ROOT_DIR/bin"
    g++ -std=c++17 -O3 -Wall -Wextra -Wpedantic \
        "$ROOT_DIR/01-dictionary-trie-hashtable-cpp/src/004final.cpp" \
        "$ROOT_DIR/01-dictionary-trie-hashtable-cpp/src/diccionario.cpp" \
        "$ROOT_DIR/01-dictionary-trie-hashtable-cpp/src/arbolTrie.cpp" \
        "$ROOT_DIR/01-dictionary-trie-hashtable-cpp/src/TablaHash.cpp" \
        -o "$BIN"
fi

ACTUAL="$SCRIPT_DIR/actual_output.txt"
"$BIN" < "$SCRIPT_DIR/sample_input.txt" | tr -d '\r' > "$ACTUAL"
tr -d '\r' < "$SCRIPT_DIR/expected_output.txt" > "${ACTUAL}.expected"

if diff -u "${ACTUAL}.expected" "$ACTUAL"; then
    rm -f "$ACTUAL" "${ACTUAL}.expected"
    echo "[PASS] All functional, UTF-8 normalization, LCRS Trie (<alarga>), and Hash Table (<saco>) tests passed."
else
    rm -f "$ACTUAL" "${ACTUAL}.expected"
    echo "[FAIL] Output mismatch detected."
    exit 1
fi
