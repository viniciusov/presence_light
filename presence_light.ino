#include <Ultrasonic.h> //https://github.com/filipeflop/Ultrasonic
#include <Narcoleptic.h> //https://github.com/brabl2/narcoleptic
 
#define trigger_pin 2
#define echo_pin 4
#define led_out 10
#define distance 120
//#define DEBUG //Comment out this line to disable DEBUG

#ifdef DEBUG
 #define debug_begin(x) Serial.begin(x);
 #define debug_print(x) Serial.print(x);
 #define debug_println(x) Serial.println(x);
 #define debug_flush(x) Serial.flush(x);
#else
 #define debug_begin(x)
 #define debug_print(x)
 #define debug_println(x)
 #define debug_flush(x)  
#endif

Ultrasonic ultrasonic(trigger_pin, echo_pin);
long n = 0;
int m, i = 0;
float cmMsec;
long microsec;

void turnon() {
 for(n=0; n<1000; n++) { //Takes 2s
  for(m=0; m<2; m++) {
   digitalWrite(10, LOW);
   delayMicroseconds(n);
   digitalWrite(10, HIGH);
   delayMicroseconds(1000-n);
  }  
 }
digitalWrite(10, LOW); 
}

void turnoff() {
 for(n=1000; n>0; n--) { //Takes 2s
  for(m=0; m<2; m++) {
   digitalWrite(10, LOW);
   delayMicroseconds(n);
   digitalWrite(10, HIGH);
   delayMicroseconds(1000-n);
  }
 } 
}

void setup() {
  debug_begin(9600);
  pinMode(led_out, OUTPUT);

  for(i=0;i<3;i++) { //Blinks 3 times when it starts
   digitalWrite(led_out, LOW);
   Narcoleptic.delay(500);
   digitalWrite(led_out, HIGH);
   Narcoleptic.delay(500);  
  }
}

void dist_measure() {
  microsec = ultrasonic.timing(); //Read sensor data (inches and cm)
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  debug_print("Distance (cm): ");
  debug_println(cmMsec);
  debug_flush();  
}
 
void loop() {
 dist_measure();
 Narcoleptic.delay(100);

  if(cmMsec <= distance) {
   debug_println("Measuring again..."); //Measures again to avoid errors
   dist_measure();

   if(cmMsec <= 120) {
    debug_println("Obstacle detected!");
    turnon();
  
    for(i=0;i<18;i++) { //Takes 90s (excluding time to turn on/off)
     Narcoleptic.delay(5000); //Library doesn't accept more than 8s delay (uses the  WDT)
    }
   
    turnoff();
   }
   else { //If second measure doesn't mach, gives a delay before returning to main loop
    Narcoleptic.delay(100);
   }
  }
}
