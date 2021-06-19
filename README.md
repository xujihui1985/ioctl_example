### ioctl example

this is an example in how to use ioctl in linux

- install kernel-devel and kernel-headers

```
sudo yum -y install kernel-devel kernel-headers
```

- build ko

```
make
```

- insmod

```
insmod ioctl_example.ko
```

- check dmesg

```
dmesg | tail --10
```

- mknod

```
 sudo mknod /dev/mydevice c 64 0
```

- build test client
```
gcc test.c
```

- run test

```
sudo ./test
```



