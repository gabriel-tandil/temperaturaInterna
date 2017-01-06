/*
DS3231_test.pde
Eric Ayars
4/11

Test/demo of read routines for a DS3231 RTC.

Turn on the serial monitor after loading this to check if things are
working as they should.

*/

#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;


void setup() {
  // Start the I2C interface
  Wire.begin();
  // Start the serial interface
  Serial.begin(57600);
}

void loop() {

  // Display the temperature
//  Serial.print("T reloj=");
  Serial.print(Clock.getTemperature(), 2);
  
  Serial.print('\n');
//  Serial.print("T arduino=");
   Serial.print(conv_temp(read_temp()), 1);
Serial.print('\n');
  delay(300);

}
// Read Atmega328P internal temperature sensor //
long read_temp()
{
  // Read temperature sensor against 1.1V reference
  ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
  // Start AD conversion
  ADCSRA |= _BV(ADEN) | _BV(ADSC);
  // Detect end-of-conversion
  while (bit_is_set(ADCSRA,ADSC));
  // return raw data
  return ADCL | (ADCH << 8);
}
 
// Convert raw temperature data to °C
double conv_temp(long raw_temp)
{
  // f(x) = (raw - offset) / coeff
  return((raw_temp - 316.61) / 1.22);
}
 
