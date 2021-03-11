# 环境配置
## LLVM && Clang
LLVM与Clang均使用10.0.0或者10.0.1版本。
可以使用
```bash
sudo apt-get install llvm

sudo apt-get install clang
```
来安装环境。

## yaml-cpp
yaml为序列化语言，类似json，pb等。
```bash
git clone https://github.com/jbeder/yaml-cpp
cd yaml-cpp
mkdir build
cd build
cmake
make
sudo ake install
```
## z3
z3是约束求解器。注意需要使用Cmake编译方式，不然可能会出现无法本项目找不到 Z3CONFIG.cmke 的情况。
```bash
git clone https://github.com/Z3Prover/z3
cd z3
mkdir build
cd build
cmake
make
sudo make install
```
## spot 2.9.4
spot为自动机相关的库。
下载地址http://lists.lrde.epita.fr/pipermail/spot-announce/2020q3/000085.html
解压后
```bash
mkdir build
cd build
cmake
make
sudo make install
```
本溪项目构建也可以采用同样的方式。最终可执行文件为`/build/bin/exec`.