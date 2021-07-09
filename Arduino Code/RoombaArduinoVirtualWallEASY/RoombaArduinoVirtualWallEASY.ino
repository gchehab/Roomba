/*
  A trivial Arduino sketch to mimic iRobot Virtual Wall for Roomba
Youtube : http://www.youtube.com/mkmeorg Website, Forum and store are at http://mkme.org
Parts needed
Arduino NANO https://amzn.to/2EaMzZI
IR LED https://amzn.to/2QOqUgE
Resistor https://amzn.to/2EhIbsf
  ----------------------------------------------------------------
  Based on information found at:
  http://sites.google.com/site/irobotcreate2/createanirbeacon
  
  Uses "A Multi-Protocol Infrared Remote Library for the Arduino":
  http://www.arcfn.com/2009/08/multi-protocol-infrared-remote-library.html
*/

#include <IRremote.h>

// Initiate IRremote on Pin 3.
IRsend irsend;
//int RXLED = 17;  // The RX LED has a defined Arduino pin
int i=0;

void setup()
{
  irsend.enableIROut(38);//Lib function
  // pinMode(RXLED, OUTPUT);  // Set RX LED as an output
  // TX LED is set as an output behind the scenes

  Serial.begin(9600); //This pipes to the serial monitor
  Serial.println("Initialize Serial Monitor");

  Serial1.begin(9600); //This is the UART, pipes to sensors attached to board
  Serial1.println("Initialize Serial Hardware UART Pins");}

void loop()
{
  //digitalWrite(RXLED, LOW);   // set the RX LED ON
  TXLED0; //TX LED is not tied to a normally controlled pin so a macro is needed, turn LED OFF
  delay (1000);

  for (i=0; i<8; i++) {
    irsend.mark(1000);
    irsend.space(1000);
  }
  
  //digitalWrite(RXLED, HIGH);    // set the RX LED OFF
  TXLED1; //TX LED macro to turn LED ON
  delay (1000);

  for (i=0; i<8; i++) {
    irsend.mark(1000);
    irsend.space(1000);
  }
}
