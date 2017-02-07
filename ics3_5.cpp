#include"ics3_5.hpp"
#include<wiringPi.h>
#include<wiringSerial.h>

void serial_open(void)
{
  int fd = serialOpen("/dev/ttyAMA0",115200);
  if(fd<0)printf("cannot open serialport\n");
  return fd;
}

SERVO::SERVO(int id_num)
{
  id = id_num;
}
