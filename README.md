# LindusOS


##Source Tree
 
Bootloader\
      bootsector\                          - stage 1 bootloader - loads the stage 2 bootloader
      bootloader-stage2\                   - stage 2 bootloader - loads the hardware abstraction layer
 
core\ 
      build\                                - Release builds
      include\                              - Standard Library Include directory
 
      lib\                                  - Compiler Specific Standard Library Runtime
      hal\                                  - Hardware Abstraction Layer
      kernel\                               - Kernel
