#include <nuttx/config.h>
#include <nuttx/syslog/syslog.h>
#include <stdio.h>
#include <unistd.h>
#include "movement.h"

/* 使用公用方法库中的函数，不再需要这里的set_motor函数 */

/* 使用公用方法库中的函数，不再需要这里的mecanum_drive函数 */

int main(int argc, char* argv[])
{
  syslog(LOG_INFO, "Mecanum RoboCar started\n");
  
  /* 初始化小车 */
  init();
  
  /* 演示各种动作 */
  while(1) {
    /* 基本动作演示 */
    syslog(LOG_INFO, "演示：前进\n");
    move_forward(0.7f);
    usleep(2000000);
    
    syslog(LOG_INFO, "演示：后退\n");
    move_backward(0.7f);
    usleep(2000000);
    
    syslog(LOG_INFO, "演示：向左平移\n");
    move_left(0.7f);
    usleep(2000000);
    
    syslog(LOG_INFO, "演示：向右平移\n");
    move_right(0.7f);
    usleep(2000000);
    
    /* 对角线动作演示 */
    syslog(LOG_INFO, "演示：左前方移动\n");
    move_forward_left(0.7f);
    usleep(2000000);
    
    syslog(LOG_INFO, "演示：右前方移动\n");
    move_forward_right(0.7f);
    usleep(2000000);
    
    /* 旋转动作演示 */
    syslog(LOG_INFO, "演示：原地逆时针旋转\n");
    rotate_counterclockwise(0.7f);
    usleep(2000000);
    
    syslog(LOG_INFO, "演示：原地顺时针旋转\n");
    rotate_clockwise(0.7f);
    usleep(2000000);
    
    /* 复杂动作演示 */
    syslog(LOG_INFO, "演示：顺时针画圈\n");
    circle_clockwise(0.7f, 0.5f);
    usleep(3000000);
    
    syslog(LOG_INFO, "演示：S形路径\n");
    for (int i = 0; i < 100; i++) {
      move_s_path(0.5f, 0.7f);
      usleep(50000);  /* 每50ms更新一次 */
    }
    
    /* 停止 */
    syslog(LOG_INFO, "演示：停止\n");
    stop();
    usleep(2000000);
  }
  
  return 0;
}