# riscv-mykernel
## 前言
[mykernel 2](https://github.com/mengning/mykernel/tree/master) 是《庖丁解牛 Linux 操作系统分析》的作者提供的一个实验平台。本项目通过修改汇编代码和数据结构，使得 `mykernel 2` 得以在 RISC-V 架构上的开发板上运行。

## 使用方法
克隆后，在与 riscv-mykernel 同级下的目录， 下载 linux-5.19.16 版本的 Linux 内核并解压， 使用以下的命令进行补丁操作：

``` bash
patch -p1 < ../kernel.patch
```
详细操作可参考 [《RISC-V Linux 内核分析实验手册》](https://github.com/Elonisme/RiSCV-Linux) 。
