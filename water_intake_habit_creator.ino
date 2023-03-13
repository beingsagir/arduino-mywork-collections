#include <TM1637Display.h>
#include <HCSR04.h>


// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   1000

HCSR04 hc(5, 6); //initialisation class HCSR04 (trig pin , echo pin)


TM1637Display display(CLK, DIO);

int count = 0;
uint8_t data[] = {0, 0, 0, 0};
  
void setup() {
Serial.begin(9600); 
}



void loop() {
  float distance = hc.dist();
  Serial.println( distance ); //return current distance (cm) in serial
  delay(60);                   // we suggest to use over 60ms measurement cycle, in order to prevent trigger signal to the echo signal.


  if(distance != 0 && distance <10.0){
    
    Serial.println( "yes" );
  }else {
    count = 0;
    Serial.println( "no" );
  }

  
  display.setBrightness(0x0a);

  data[3] = display.encodeDigit(count/1 % 10);
  data[2] = display.encodeDigit(count/10 % 10);
  data[1] = display.encodeDigit(count/100 % 10);
  data[0] = display.encodeDigit(count/1000 % 10);
  //display.setSegments(data);
  int minutes = count/60;
  int seconds = count%60;
  display.showNumberDecEx(seconds, 0, true, 2, 2);
  display.showNumberDecEx(minutes, 0b01000000, true, 2, 0);

  if(count > 9998) {
    display.setSegments(data);
  } else {
    count++;
  }
  
  delay(TEST_DELAY);
}
