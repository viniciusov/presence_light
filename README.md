# Presence Light

With this simple code, you can transform your Arduino + Ultrasonic sensor + some LEDs in a presence light system.
Everytime someone or something pass in front the sensor, the lights will turn on.

Just build your light system (using LEDs) and connect the Arduino Pin #10 as a COMMON CATHODE.  
**PS: Don't forget to check the maximum current per pin for your arduino board!**

The code was originally created to the Arduino NANO, so I had to create a PWM-like function, to make the lights turn on/off smoothly.

Change the line below to monitor the desired distance:  
`#define distance 120`

If you need to see some Debug messages, remove the comment mark `//` in:  
`//#define DEBUG`
