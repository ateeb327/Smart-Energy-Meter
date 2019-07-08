float current=0.000f;
//Smart Energy meter by Muhammad Ateeb Aslam
// Find me on github.com/ateeb327
//This code is Optimized for NodeMCU board, However, it can work for any ESP compatible board privided that
// you adjust the adc_zero value according to respective board.

/*   Smart Enery Meter can Sense current and Notify user of the power consumption at current time.  
 *   ACS712 Sensor is connected  to Pin A0 on NodeMCU.
 *   Sensed current will be published to thingSpeak.com
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
WiFiClient client;

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey  = "YOUR-WRITE-API-KEY";  //replace with your write API Key from thingSpeak
String request_string; 

HTTPClient http;


const int currentPin = A0;     
const unsigned long sampleTime = 100000UL;                           // sample over 100ms, it is an exact number of cycles for both 50Hz and 60Hz mains
const unsigned long numSamples = 500UL;                               // choose the number of samples to divide sampleTime exactly, but low enough for the ADC to keep up
const unsigned long sampleInterval = sampleTime/numSamples;  // the sampling interval, must be longer than then ADC conversion time
const int adc_zero = 800;                                         // relative digital zero of the arudino input from ACS712 (could make this a variable and auto-adjust it)
float data[500];                                       //(digital zero)511 in case of Arduino UNO //760 for NodeMCU

void setup()
{
 Serial.begin(115200);
 WiFi.disconnect();
   WiFi.begin("ateeb327","@abcd1234");                    //Replace these values with your own WiFi Network parameters
  while ((!(WiFi.status() == WL_CONNECTED))){
     Serial.print(".");
  }
 delay(1000);

}

void loop()
{
flushincoming();
CurrentSense();
thingspeakupdate();       //Update Sensed current to thingSpeak Cloud
//Serial.println(analogRead(currentPin));

Serial.println(current);
delay(1000);

}

void CurrentSense()
{
// unsigned long currentAcc = 0;
 unsigned int count = 0;
 unsigned long prevMicros = micros() - sampleInterval ;
 while (count < numSamples)
 {
   if (micros() - prevMicros >= sampleInterval)
   {
     data[count] = analogRead(currentPin) - adc_zero;
     data[count] += (unsigned long)(data[count] * data[count]); //findin squares
     count=count+1;
     prevMicros += sampleInterval;
   }
 }
  float sum=0;
  for(int i=0;i<500;i++){
       sum = sum+data[i];  //findin sum for mean
  }
 float rms = sqrt((float)sum/(float)numSamples) * (76 / 1320.0);   //squareroot //RMS //1024 for Arduino UNO
rms=rms-0.09;
//if (rms<=0.03)
//{
//rms=0;
//}

current=rms;
}
void flushincoming(){
   while(Serial.available())
  Serial.read();
  }

void thingspeakupdate(){
     if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "api_key=";
      request_string += writeAPIKey;
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += current;
      http.begin(request_string);
      http.GET();
      http.end();
      delay(100);

    }
}

