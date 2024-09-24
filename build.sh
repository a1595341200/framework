###
 # @Author: yao.xie 1595341200@qq.com
 # @Date: 2023-09-13 13:47:31
 # @LastEditors: a1595341200 1595341200@qq.com
 # @LastEditTime: 2024-09-04 15:40:38
 # @FilePath: /cplusplus/build.sh
 # @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
### 
clear

# git submodule init
# git submodule update

SCRIPT_DIR=$(cd $(dirname $0); pwd)

build_framework() {
      cmake -DCMAKE_BUILD_TYPE=Debug                  \
            -DCMAKE_PREFIX_PATH=$SCRIPT_DIR/build_install \
            -DCMAKE_INSTALL_PREFIX=$SCRIPT_DIR/build_install  \
            -S . -B ./build -G "Unix Makefiles"

      cmake --build ./build

      cmake --install ./build
}

build_framework
