#include "Movement.h"

void setup() {
  // 初始化串口通信，用于调试输出
  Serial.begin(115200);
  Serial.println("麦克纳姆轮小车启动");
  
  // 初始化小车
  init();
}

void loop() {
  // 演示各种动作
  
  // 基本动作演示
  Serial.println("演示：前进");
  move_forward(0.7);
  delay(2000);
  
  Serial.println("演示：后退");
  move_backward(0.7);
  delay(2000);
  
  Serial.println("演示：向左平移");
  move_left(0.7);
  delay(2000);
  
  Serial.println("演示：向右平移");
  move_right(0.7);
  delay(2000);
  
  // 对角线动作演示
  Serial.println("演示：左前方移动");
  move_forward_left(0.7);
  delay(2000);
  
  Serial.println("演示：右前方移动");
  move_forward_right(0.7);
  delay(2000);
  
  // 旋转动作演示
  Serial.println("演示：原地逆时针旋转");
  rotate_counterclockwise(0.7);
  delay(2000);
  
  Serial.println("演示：原地顺时针旋转");
  rotate_clockwise(0.7);
  delay(2000);
  
  // 复杂动作演示
  Serial.println("演示：顺时针画圈");
  circle_clockwise(0.7, 0.5);
  delay(3000);
  
  Serial.println("演示：S形路径");
  for (int i = 0; i < 100; i++) {
    move_s_path(0.5, 0.7);
    delay(50);  // 每50ms更新一次
  }
  
  // 停止
  Serial.println("演示：停止");
  stop();
  delay(2000);
}
