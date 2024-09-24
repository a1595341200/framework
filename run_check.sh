# run-clang-tidy -p build > clang-tidy-report.txt
###
 # @Author: yao.xie 1595341200@qq.com
 # @Date: 2024-03-20 23:53:59
 # @LastEditors: yao.xie 1595341200@qq.com
 # @LastEditTime: 2024-04-09 16:55:10
 # @FilePath: /cplusplus/run_check.sh
 # @Description: 
 # 
 # Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
### 
# cppcheck --enable=all \
#          --language=c++ --output-file=cppcheck.txt -q  \
#          --suppressions-list=./suppressions.txt         \
#          --std=c++17 --template=gcc --inconclusive ./src ./submodule/algorithmBase\
#          -i ./build

cppcheck --enable=all \
         --language=c++ --output-file=cppcheck.txt -q  \
         --std=c++17 --template=gcc --inconclusive ./src ./include\
         -i ./build
