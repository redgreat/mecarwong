#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <stdbool.h>

/**
 * @brief 初始化麦克纳姆轮小车
 * 
 * 配置所有必要的GPIO和PWM引脚
 */
void init(void);

/**
 * @brief 控制小车前进
 * 
 * @param speed 速度值，范围0.0-1.0
 */
void move_forward(float speed);

/**
 * @brief 控制小车后退
 * 
 * @param speed 速度值，范围0.0-1.0
 */
void move_backward(float speed);

/**
 * @brief 控制小车向左平移
 * 
 * @param speed 速度值，范围0.0-1.0
 */
void move_left(float speed);

/**
 * @brief 控制小车向右平移
 * 
 * @param speed 速度值，范围0.0-1.0
 */
void move_right(float speed);

/**
 * @brief 控制小车左前方移动（对角线移动）
 * 
 * @param speed 速度值，范围0.0-1.0
 */
void move_forward_left(float speed);

/**
 * @brief 控制小车右前方移动（对角线移动）
 * 
 * @param speed 速度值，范围0.0-1.0
 */
void move_forward_right(float speed);

/**
 * @brief 控制小车左后方移动（对角线移动）
 * 
 * @param speed 速度值，范围0.0-1.0
 */
void move_backward_left(float speed);

/**
 * @brief 控制小车右后方移动（对角线移动）
 * 
 * @param speed 速度值，范围0.0-1.0
 */
void move_backward_right(float speed);

/**
 * @brief 控制小车原地顺时针旋转
 * 
 * @param speed 速度值，范围0.0-1.0
 */
void rotate_clockwise(float speed);

/**
 * @brief 控制小车原地逆时针旋转
 * 
 * @param speed 速度值，范围0.0-1.0
 */
void rotate_counterclockwise(float speed);

/**
 * @brief 控制小车顺时针画圈
 * 
 * @param speed 速度值，范围0.0-1.0
 * @param radius 圆的半径，值越大，圆越大
 */
void circle_clockwise(float speed, float radius);

/**
 * @brief 控制小车逆时针画圈
 * 
 * @param speed 速度值，范围0.0-1.0
 * @param radius 圆的半径，值越大，圆越大
 */
void circle_counterclockwise(float speed, float radius);

/**
 * @brief 控制小车沿S形路径移动
 * 
 * @param speed 速度值，范围0.0-1.0
 * @param amplitude S形的振幅
 */
void move_s_path(float speed, float amplitude);

/**
 * @brief 立即停止小车所有动作
 */
void stop(void);

/**
 * @brief 自定义小车运动
 * 
 * @param vx X方向速度，前为正，后为负，范围-1.0到1.0
 * @param vy Y方向速度，左为负，右为正，范围-1.0到1.0
 * @param omega 旋转速度，逆时针为正，顺时针为负，范围-1.0到1.0
 */
void custom_move(float vx, float vy, float omega);

#endif /* MOVEMENT_H */
