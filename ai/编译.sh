# 建立 NuttX 应用
cd spresense/sdk
tools/create_newapp.sh mecanum_car      # 生成样板


# 编译
cd nuttx
make distclean
tools/config.py -m spresense mecanum_car    # 选中新应用
make -j
tools/flash.sh   # 烧录

预留扩展：蓝牙 & 传感器

蓝牙：Spresense 扩展板自带 UART0 & UART2，后期可接 HC-05 或使用 CXD5602 上的 BLE 模组（SDK 内置 bluenet）。
I²C / SPI 传感器：扩展板留有 SDA/SCL & SPI0-4，引脚由 board.h 给出。
建议把通信／传感器驱动写成 NuttX 线程，与 mecanum_drive() 共享消息队列；这样运动控制与高层逻辑解耦。

下一步建议

先验证四个轮子正/反转，确认 PWM 占空比方向一致；若轮序不同，只需调整数组。
加入陀螺仪（MPU6050）反馈，做闭环；Spresense 有 DSP，可跑简易 PID。
将上位机指令（蓝牙 / Wi-Fi / UART）解析为 vx, vy, ω，并送入 mecanum_drive()。

