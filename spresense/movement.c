#include "movement.h"
#include <nuttx/config.h>
#include <nuttx/syslog/syslog.h>
#include <arch/board/board.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#define PWM_FREQ 20000   /* 20 kHz 减噪音 */
static const int pwm_channels[4] = { 2, 3, 5, 6 }; /* D2-D6 对应 PWM */
static const int dir_pins[4][2] = {
    {4, 7},    /* 电机0的方向引脚 */
    {8, 12},   /* 电机1的方向引脚 */
    {13, 10},  /* 电机2的方向引脚 */
    {11, 9}    /* 电机3的方向引脚 */
};

/* 麦克纳姆轮参数 */
static const float WHEEL_RADIUS = 0.05;  /* 轮子半径，单位米 */
static const float CAR_LENGTH = 0.12;    /* 小车长度，单位米 */
static const float CAR_WIDTH = 0.12;     /* 小车宽度，单位米 */

/**
 * @brief 设置单个电机的速度和方向
 * 
 * @param idx 电机索引（0-3）
 * @param duty 占空比（0.0-1.0）
 * @param dir 方向（true=正向，false=反向）
 */
static void set_motor(int idx, float duty, bool dir)
{
    int pwm = pwm_channels[idx];
    board_pwm_setup(pwm, PWM_FREQ);
    board_pwm_start(pwm, fabsf(duty));  /* 0-1 占空比 */

    /* DIR 引脚：高=前进，低=后退 */
    board_gpio_write(dir_pins[idx][0], dir);
    board_gpio_write(dir_pins[idx][1], !dir);
}

/**
 * @brief 麦克纳姆轮运动学控制
 * 
 * @param vx X方向速度（前后方向）
 * @param vy Y方向速度（左右方向）
 * @param omega 旋转角速度
 */
static void drive(float vx, float vy, float omega)
{
    float w[4];
    w[0] = (vx - vy - (CAR_LENGTH + CAR_WIDTH) * omega) / WHEEL_RADIUS;
    w[1] = (vx + vy + (CAR_LENGTH + CAR_WIDTH) * omega) / WHEEL_RADIUS;
    w[2] = (vx + vy - (CAR_LENGTH + CAR_WIDTH) * omega) / WHEEL_RADIUS;
    w[3] = (vx - vy + (CAR_LENGTH + CAR_WIDTH) * omega) / WHEEL_RADIUS;

    /* 归一化处理，确保所有速度在-1到1范围内 */
    float maxw = 0;
    for (int i = 0; i < 4; i++) {
        if (fabsf(w[i]) > maxw) {
            maxw = fabsf(w[i]);
        }
    }
    
    if (maxw > 1.0f) {
        for (int i = 0; i < 4; i++) {
            w[i] /= maxw;
        }
    }

    /* 设置每个电机的速度和方向 */
    for (int i = 0; i < 4; i++) {
        set_motor(i, fabsf(w[i]), w[i] >= 0);
    }
}

void init(void)
{
    syslog(LOG_INFO, "Initializing Mecanum RoboCar\n");
    
    /* 配置所有方向引脚为输出 */
    for (int i = 0; i < 4; i++) {
        board_gpio_config(dir_pins[i][0], GPIO_OUTPUT);
        board_gpio_config(dir_pins[i][1], GPIO_OUTPUT);
    }
    
    /* 初始化时停止所有电机 */
    stop();
    
    syslog(LOG_INFO, "Mecanum RoboCar initialized successfully\n");
}

void move_forward(float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    drive(speed, 0.0f, 0.0f);
}

void move_backward(float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    drive(-speed, 0.0f, 0.0f);
}

void move_left(float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    drive(0.0f, -speed, 0.0f);
}

void move_right(float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    drive(0.0f, speed, 0.0f);
}

void move_forward_left(float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    float component = speed / sqrtf(2.0f);  /* 对角线分量 */
    drive(component, -component, 0.0f);
}

void move_forward_right(float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    float component = speed / sqrtf(2.0f);  /* 对角线分量 */
    drive(component, component, 0.0f);
}

void move_backward_left(float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    float component = speed / sqrtf(2.0f);  /* 对角线分量 */
    drive(-component, -component, 0.0f);
}

void move_backward_right(float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    float component = speed / sqrtf(2.0f);  /* 对角线分量 */
    drive(-component, component, 0.0f);
}

void rotate_clockwise(float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    drive(0.0f, 0.0f, -speed);
}

void rotate_counterclockwise(float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    drive(0.0f, 0.0f, speed);
}

void circle_clockwise(float speed, float radius)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    /* 圆周运动需要线速度和角速度的组合 */
    float linear_speed = speed;
    float angular_speed = speed / (radius + 0.1f);  /* 防止除零 */
    
    drive(linear_speed, 0.0f, -angular_speed);
}

void circle_counterclockwise(float speed, float radius)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    /* 圆周运动需要线速度和角速度的组合 */
    float linear_speed = speed;
    float angular_speed = speed / (radius + 0.1f);  /* 防止除零 */
    
    drive(linear_speed, 0.0f, angular_speed);
}

void move_s_path(float speed, float amplitude)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    
    /* S形路径可以通过动态调整角速度实现 */
    /* 这里使用简化实现，实际应用中可能需要更复杂的轨迹规划 */
    static float phase = 0.0f;
    float omega = amplitude * sinf(phase);
    
    phase += 0.05f;
    if (phase > 2 * M_PI) {
        phase -= 2 * M_PI;
    }
    
    drive(speed, 0.0f, omega);
}

void stop(void)
{
    drive(0.0f, 0.0f, 0.0f);
}

void custom_move(float vx, float vy, float omega)
{
    /* 限制输入范围在-1到1之间 */
    if (vx < -1.0f) vx = -1.0f;
    if (vx > 1.0f) vx = 1.0f;
    
    if (vy < -1.0f) vy = -1.0f;
    if (vy > 1.0f) vy = 1.0f;
    
    if (omega < -1.0f) omega = -1.0f;
    if (omega > 1.0f) omega = 1.0f;
    
    drive(vx, vy, omega);
}
