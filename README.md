# Active-Foldable-Quadrotor
The active foldable quadrotor
![image](https://user-images.githubusercontent.com/70571986/212499838-8d5ddd4b-a0a9-42d2-bccc-d256f7672544.png)


motor_control.ino = You may use Arduino for this code for running the 4 motors of active foldable quadrotors. It can receive the motor commands from the ROS 
motion control node running on the raspberry pi 4b. The PWM Fast timers generates 400 Hz PWM signal for the motors. Servos are running on 50 Hz.
