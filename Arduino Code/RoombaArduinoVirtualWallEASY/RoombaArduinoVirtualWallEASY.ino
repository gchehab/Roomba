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
#define DEBUG
#undef DEBUG

#include <IRremote.h>
void roomba_send(int code); 

// Initiate IRremote on Pin 3.
IRsend irsend;
int RXLED = 17;  // The RX LED has a defined Arduino pin
int i=0;
unsigned int *raw;
int length = 8;
  
void setup()
{
  // pinMode(RXLED, OUTPUT);  // Set RX LED as an output
  // TX LED is set as an output behind the scenes

  #ifdef DEBUG
  Serial.begin(9600); //This pipes to the serial monitor
  Serial.println("Initialize Serial Monitor");
  
  Serial1.begin(9600); //This is the UART, pipes to sensors attached to board
  Serial1.println("Initialize Serial Hardware UART Pins");
  #endif
  irsend.enableIROut(38);//Lib function
  irsend.setSendPin(3);

  raw = calloc (length*2, sizeof(unsigned int));
  roomba_code2raw(162);
}

void loop()
{
  //digitalWrite(RXLED, LOW);   // set the RX LED ON
  TXLED0; //TX LED is not tied to a normally controlled pin so a macro is needed, turn LED OFF
  //delay (1000);

  for (i=0; i < 15; i++)
    roomba_send (162);
  
  //digitalWrite(RXLED, HIGH);    // set the RX LED OFF
  TXLED1; //TX LED macro to turn LED ON
  //delay (1000);
  roomba_send (162);

}

void roomba_code2raw(int code) 
{
  #ifdef DEBUG
  Serial.print("Genratiing Roomba code ");
  Serial.print(code);
  #endif
  
  unsigned int one_pulse = 3000;
  unsigned int one_break = 1000;
  unsigned int zero_pulse = one_break;
  unsigned int zero_break = one_pulse;
  
  int arrayposition = 0;
  // Serial.println("");
  for (int counter = length-1; counter >= 0; --counter) {
    if(code & (1<<counter)) {
      // Serial.print("1");
      raw[arrayposition] = one_pulse;
      raw[arrayposition+1] = one_break;
    } 
    else {
      // Serial.print("0");
      raw[arrayposition] = zero_pulse;
      raw[arrayposition+1] = zero_break;
    }
    arrayposition = arrayposition + 2;
  } 
}

void roomba_send(int code) 
{
  #ifdef DEBUG
  Serial.print("Sending Roomba code ");
  Serial.print(code);
  #endif
  
  for (int i = 0; i < 3; i++) {
    irsend.sendRaw(raw, 15, 38);
    delay(50);
  }

  #ifdef DEBUG
  Serial.println("");

  Serial.print("Raw timings:");
  for (int z=0; z<length*2; z++) {
    Serial.print(" ");
    Serial.print(raw[z]);
  }
  Serial.print("\n\n");
  #endif
}
