# Active-Foldable-Quadrotor
The active foldable quadrotor

![image](https://user-images.githubusercontent.com/70571986/212499896-54cb0d8b-625f-4980-beb1-62b1e0a3221d.png)


motor_control.ino = You may use Arduino for this code for running the 4 motors of active foldable quadrotors. It can receive the motor commands from the ROS 
motion control node running on the raspberry pi 4b. The PWM Fast timers generates 400 Hz PWM signal for the motors. Servos are running on 50 Hz.
