# LindusOS

##Source Tree
 
      bootloader\
            bootsector\                          - stage 1 bootloader - loads the stage 2 bootloader
            bootloader-stage2\                   - stage 2 bootloader - loads the hardware abstraction layer
 
      core\ 
            build\                                - Release builds
            include\                              - Standard Library Include directory 
            lib\                                  - Compiler Specific Standard Library Runtime
            hal\                                  - Hardware Abstraction Layer
            kernel\                               - Kernel

### Build Instructions
The bootsector and bootloader do NOT have makefiles. 
* Assembling 'bootsec.asm' will output the bootsector in binary.
* Assembling 'BTLSTG2.asm' will output the stage 2 bootloader in binary.

The core has a makefile in its root directory. The 'lib', 'hal' and the 'kernel' folder have a make configuration file named 'make.config'. The aforementioned folders also have their own makefile.

However, to build the core, the makefile in the root directory must be executed. This makefile will automatically execute the makefiles in the sub directories.

###Hardware Abstraction Layer List:
* x86

The kernel is independent of the architecture and hardware. Architecture specifications are controlled by the hardware abstraction layer. The hardware abstraction layer provides an "interface" to the kernel which is completely independent of the hardware present.

#### Choosing Architecture
Architecture configurations must be set in hal/make.config. Every architecture folder must have its own makefile. The makefile in the root directory will build the correct hardware abstraction layer and link it to the kernel.
