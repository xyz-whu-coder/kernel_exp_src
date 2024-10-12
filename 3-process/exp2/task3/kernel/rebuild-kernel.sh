cd kernel

make clean
make mrproper

make openeuler_defconfig

clear
make -j4 Image > make-image-output.log
make -j4 modules > make-modules-output.log
make dtbs

make modules_install
make install

reboot
