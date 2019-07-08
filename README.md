# Smart-Energy-Meter
This project utilizes NodeMCU board with ACS712 Current Sensor to read Current and publish the sensed current to thingSpeak Cloud, which in turn can be collected via an Android app made on MIT App Inventor

# ThingSpeak Setup
      Sign Up on thingSpeak.com, Create a Channel and get WriteAPIKey so that we can write data on the cloud. 
      Copy and Past the write API key you got in the following Line in Code.
      String writeAPIKey  = "YOUR-WRITE-API-KEY";
      
# WiFi Configuration: 
              WiFi.begin("ateeb327","@abcd1234"); 
Configure the above Lines in code with you WiFi Network SSID and Password. 

# Adjust ADC value- Optional:
           This code is Optimized for NodeMCU board. However, if you are using any other board,
           adjust the adc value in following Line:
           const int adc_zero = 800;
           Otherwise, Leave it as it is. 
# Test the Code:
After making all the necessary changes explained above, Upload Code on NodeMCU or the board you have, Open thingSpeak 
and see the Sensed Current published. 
You can also use a Multimeter to verify that the sensed current readings are correct. 

# Grab Measured Current in Android App from Anywhere
Download the MIT app Inventor project file named 'EnergyMeter.aia', go to http://ai2.appinventor.mit.edu, 
after logging in, click on New Project, Click 'Import Project (aia) from my computer'
and upload the aia file. 

Now change to 'Blocks' view from 'Designer' view in the upper left corner on Screen and write your thingSpeak Channel Id 
ReadApiKey in the respective blocks as shown below:
![alt text](https://i.imgur.com/01nen1X.png)

Click on Build > Provide QR Code for APK. Scan QR code and Download the app APK File Install and
Click on Button 'Get Sensed Current' to see the currently sensed current value. Enjoy!
