/*
compile option:-std=c++11 -lwiringPi
*/

#include<wiringPi.h>
#include<wiringSerial.h>

int serial_open(void)
{
  int fd = serialOpen("/dev/ttyAMA0",115200);
  if(fd<0)printf("cannot open serialport\n");
  return fd;
}
//send data
inline void send_data(int fd){}
template<typename First, typename... Rest>
void send_data(int fd, First& first, Rest&... rest)
{
  serialPutchar((char)first);
  send_data(fd, rest...);
}

#include<string>
using std::string;
string receive_data(int fd)
{
  string data;
  while(serialDataAvail(fd))
  {
    data += serialGetchar(fd);
  }
  return string;
}

//rotate servo
const double pi = 3.1415926;
const int angle_newtral = 7500;
const int angle_width = 4000;//3500~11500
inline int rad2angle(double radian){return radian/pi*angle_width+angle_newtral;}
inline double angle2rad(string data)
{
  int angle = ((int)data[0]>>1)|(int)data[1];
  return (double)((angle-angle_newtral)*angle_width)/pi;
}
double servo_move(int fd,unsigned int id,double radian)
{
  int angle = rad2angle(radian)
  send_data(fd,0x80|id,0x7f&(angle>>7),0x7f&angle);
  return angle2rad(receive_data(fd));
}
void servo_free(int fd,unsigned int id)
{
  send_data(fd,0x80|id,0,0);
  serialFlush(fd);
}

//read param
//CMD,SC->R_CMD,SC,DATA
const int cmd_read = 0xa0;
int servo_read(int fd,unsigned int id,int sc)
{
  send_data(fd,cmd_read|id,sc);
  return (int)(receive_data(fd).pop_back());//0~127
}

int servo_current(int fd,unsigned int id)
{
  int cur = servo_read(fd,id,0x03);//64~127,0~63
  if(0x80&cur==0)return cur;
  else return cur-0x80;
}
int servo_thermo(int fd,unsigned int id)
{
  return send_data(fd,id,0x04);//0~127
}

//write param
void servo_write(int fd,unsigned int id,int )
