#include <nuttx/config.h>
#include <nuttx/syslog/syslog.h>
#include <arch/board/board.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#define PWM_FREQ 20000   /* 20 kHz 减噪音 */
static const int pwm_channels[4] = { 2,3,5,6 }; /* D2-D6 对应 PWM */

static void set_motor(int idx, float duty, bool dir)
{
  int pwm = pwm_channels[idx];
  board_pwm_setup(pwm, PWM_FREQ);
  board_pwm_start(pwm, fabsf(duty));               /* 0-1 占空比 */

  /* DIR 引脚：高=前进，低=后退 */
  int dir_pin1, dir_pin2;
  switch(idx) {
    case 0: dir_pin1=4; dir_pin2=7; break;
    case 1: dir_pin1=8; dir_pin2=12; break;
    case 2: dir_pin1=13; dir_pin2=10; break;
    case 3: dir_pin1=11; dir_pin2=9; break;
  }
  board_gpio_write(dir_pin1, dir);
  board_gpio_write(dir_pin2, !dir);
}

static void mecanum_drive(float vx,float vy,float omega)
{
  const float R=0.05, L=0.12, W=0.12;
  float w[4];
  w[0]=(vx-vy-(L+W)*omega)/R;
  w[1]=(vx+vy+(L+W)*omega)/R;
  w[2]=(vx+vy-(L+W)*omega)/R;
  w[3]=(vx-vy+(L+W)*omega)/R;

  float maxw=0;
  for(int i=0;i<4;i++) if(fabsf(w[i])>maxw) maxw=fabsf(w[i]);
  if(maxw>1.0f) for(int i=0;i<4;i++) w[i]/=maxw;  /* 归一 */

  for(int i=0;i<4;i++)
    set_motor(i, w[i], w[i]>=0);
}

int main(int argc,char* argv[])
{
  syslog(LOG_INFO,"Mecanum RoboCar started\n");
  board_gpio_config(4,GPIO_OUTPUT); /* 预配置全部 DIR 引脚… */
  /* …其余同理 */

  while(1){
    mecanum_drive(1.0f, 0.0f, 0.0f); /* 向前 */
    usleep(2000000);
    mecanum_drive(0.0f,-1.0f, 0.0f); /* 向右平移 */
    usleep(2000000);
    mecanum_drive(0.0f, 0.0f, 1.0f); /* 原地左转 */
    usleep(2000000);
    mecanum_drive(0,0,0);
    usleep(1000000);
  }
  return 0;
}