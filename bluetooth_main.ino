/****
Edited CALLBACKECHO code for gait project
*****/
/*********************************************************************
This is an example for our nRF8001 Bluetooth Low Energy Breakout

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1697

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Kevin Townsend/KTOWN  for Adafruit Industries.
MIT license, check LICENSE for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

// This version uses call-backs on the event and RX so there's no data handling in the main loop!

#include <SPI.h>
#include "Adafruit_BLE_UART.h"
#include <Console.h>
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART uart = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
int max_prox=0;
int max_prox2=0;
float time_prox=0;
float time_prox2=0;

int min_sonic=250;
int min_sonic2=250;
float time_sonic=0;
float time_sonic2=0;


int min_pir=250;
int min_pir2=250;
float time_pir=0;
float time_pir2=0;

int collect=0;

int sonicPin = A0; //analog pin 0
int pirPin=A1;
int proxPin=A2;
int sonicPin2 = A3; //analog pin 0
int pirPin2=A4;
int proxPin2=A5;
int calibrationTime=10;
int proxVal;
int sonicVal;
int pirVal;
int proxVal2;
int sonicVal2;
int pirVal2;

int prox_thresh=200;
int sonic_thresh=120;
int pir_thresh=250;
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(3,4,5,6,7,8);
/**************************************************************************/
/*!
    This function is called whenever select ACI events happen
*/
/**************************************************************************/
void aciCallback(aci_evt_opcode_t event)
{
  switch(event)
  {
    case ACI_EVT_DEVICE_STARTED:
      Console.println(F("Advertising started"));
      break;
    case ACI_EVT_CONNECTED:
      {Console.println(F("Connected!"));
                lcd.clear();
          lcd.setCursor(0, 0);
  // print the number of seconds since reset:
  lcd.print("connected at ");
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
  lcd.print("s");
      }
      break;
    case ACI_EVT_DISCONNECTED:
      {Console.println(F("Disconnected or advertising timed out"));
       lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("disconnected at ");
          lcd.setCursor(0,1);
  lcd.print(millis()/1000);
  lcd.print("s");
      }
      break;
    default:
      break;
  }
}

/**************************************************************************/
/*!
    This function is called whenever data arrives on the RX channel
*/
/**************************************************************************/
void rxCallback(uint8_t *buffer, uint8_t len)
{
  Console.print(F("Received "));
  Console.print(len);
  Console.print(F(" bytes: "));
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Received ");
  char temp[10];
  for(int i=0; i<len; i++)
  { Console.print((char)buffer[i]); 
  Console.println(i);
temp[i]=(char)buffer[i];
  }
  //temp[len]='\0';
  
  lcd.print(temp);

  if (temp[2]=='a')
  {collect=1;
  Console.println("going to start now");
  }
  
  if(temp[2]=='o')
  {collect=0;
   
  
 Console.println("Stopping now");
 Console.print("Prox time  "); 
  Console.println((float)(time_prox-time_prox2)/1000);
  Console.println(time_prox);
  Console.println(time_prox2);
 lcd.clear();
 lcd.print("pro=");

 lcd.print((float)(time_prox-time_prox2)/1000);
 time_prox=0;
 time_prox2=0;
 max_prox=0;
 max_prox2=0;
 
  Console.print("sonic time  "); 
   Console.println((float)(time_sonic-time_sonic2)/1000);
  Console.println(time_sonic);
  Console.println(time_sonic2);
 lcd.setCursor(0,1);
 lcd.print("sonic=");

 lcd.print((float)(time_sonic-time_sonic2)/1000);
 time_sonic=0;
 time_sonic2=0;
 min_sonic=250;
 min_sonic2=250;
    Console.print("PIR time  "); 
    Console.println((float)(time_pir-time_pir2)/1000);
  Console.println(time_pir);
  Console.println(time_pir2);
 lcd.setCursor(8,0);
 lcd.print(" pir=");
 lcd.print((float)(time_pir-time_pir2)/1000);
 time_pir=0;
 time_pir2=0;
 min_pir=250;
 min_pir2=250;
  }
  
  Console.print(F(" ["));

  for(int i=0; i<len; i++)
  {
    Console.print(" 0x"); Console.print((char)buffer[i], HEX); 
  }
  Console.println(F(" ]"));

  /* Echo the same data back! */
  //uart.write(buffer, len);
}

/**************************************************************************/
/*!
    Configure the Arduino and start advertising with the radio
*/
/**************************************************************************/
void setup(void)
{ 
   Bridge.begin();
  Console.begin();
 
  while(!Console); // Leonardo/Micro should wait for serial init
  Console.println(F("Adafruit Bluefruit Low Energy nRF8001 Callback Echo demo"));
lcd.begin(16, 2);

 pinMode(pirPin, INPUT);
 
  digitalWrite(pirPin, LOW);
  
     pinMode(pirPin2, INPUT);
 
  digitalWrite(pirPin2, LOW);

  //give the sensor some time to calibrate
  Console.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Console.print(".");
      delay(1000);
      }
    Console.println(" done");



  // Print a message to the LCD.
  lcd.print("hello, world!");
  uart.setRXcallback(rxCallback);
  uart.setACIcallback(aciCallback);
  uart.begin();
}

/**************************************************************************/
/*!
    Constantly checks for new events on the nRF8001
*/
/**************************************************************************/
void loop()
{
  if (collect==1)
  {collectdata();
  }
  uart.pollACI();
}

void collectdata()
{

proxVal= analogRead(proxPin);
sonicVal=analogRead(sonicPin);
pirVal=analogRead(pirPin);
proxVal2 = analogRead(proxPin2);
sonicVal2=analogRead(sonicPin2);
pirVal2=analogRead(pirPin2);

  Console.print(millis());
    Console.print(" ");
  Console.print(sonicVal);

    Console.print(" ");
  Console.print(pirVal);
    Console.print(" ");
  Console.print(proxVal);
  Console.print(" ");


  Console.print(sonicVal2);
    Console.print(" ");
  Console.print(pirVal2);
    Console.print(" ");
  Console.println(proxVal2);

  

  
  if(proxVal>=prox_thresh)
  {
  if(proxVal>=max_prox)
  {
  max_prox=proxVal;
  time_prox=millis();
  }

  }
    if(proxVal2>=prox_thresh)
  {
  if(proxVal2>=max_prox2)
   {
  max_prox2=proxVal2;
  time_prox2=millis();
  }


  }
  
  
    if(sonicVal<=sonic_thresh)
  {
  if(sonicVal<=min_sonic)
  {
  min_sonic=sonicVal;
  time_sonic=millis();
  }
}
    if(sonicVal2<=sonic_thresh)
  {
  if(sonicVal2<=min_sonic2)
   {
  min_sonic2=sonicVal2;
  time_sonic2=millis();
  }

  }
  
  
  
  
    if(pirVal<=pir_thresh)
  {
  if(pirVal<=min_pir)
  {
  min_pir=pirVal;
  time_pir=millis();
  }


  }
    if(pirVal2<=pir_thresh)
  {
  if(pirVal2<=min_pir2)
   {
  min_pir2=pirVal2;
  time_pir2=millis();
  }

  }
  delay(100);
}
