#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "ioctl_test.h"

int main() {
  int answer;
  struct mystruct test = {4, "sean"};
  int dev = open("/dev/mydevice", O_WRONLY);
  if (dev == -1) {
    printf("failed to open\n");
    return -1;
  }

  ioctl(dev, RD_VALUE, &answer);
  printf("answer is %d\n", answer);

  answer = 123;
  ioctl(dev, WR_VALUE, &answer);
  ioctl(dev, RD_VALUE, &answer);
  printf("the answer is %d\n", answer);
  ioctl(dev, GREETER, &test);

  
  printf("open success\n");
  close(dev);
  return 0;
}
