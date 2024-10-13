#!/bin/bash

# 检查是否提供了源文件
if [ $# -eq 0 ]; then
    echo "Usage: $0 <source_file.cpp>"
    exit 1
fi

# 获取源文件名
SOURCE_FILE="$1"
# 获取文件名，不带扩展名
BASENAME=$(basename "$SOURCE_FILE" .cpp)
# 设置输出文件名
OUTPUT_FILE="${BASENAME}.s"

# 使用 g++ 编译器生成汇编代码
g++ -S -o "$OUTPUT_FILE" "$SOURCE_FILE"

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "Assembly code generated: $OUTPUT_FILE"
else
    echo "Compilation failed."
    exit 1
fi
