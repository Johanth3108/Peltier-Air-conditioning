#Air Conditioner Project with ESP8266 and Peltier Module

**Overview:**
This project utilizes an ESP8266 microcontroller along with a Peltier module to create a custom air conditioning system. The system is designed to control various components such as an air purifier, fan, water pump, and Peltier module based on environmental conditions and user preferences. 

**Features:**
- Control of air purifier, fan, water pump, and Peltier module via a web interface.
- Monitoring of temperature, humidity, and air quality using sensors.
- Automatic and manual control modes for the Peltier module.
- Web server implementation for remote access and control.

**Hardware Components:**
- ESP8266 microcontroller
- Peltier module
- Air purifier
- Fan
- Water pump
- Temperature and humidity sensors (DHT11)
- Air quality sensor (MQ135)
- OneWire temperature sensor (DS18B20)
- Relay modules (6-channel)

**Software Libraries Used:**
- ESP8266WiFi
- WiFiClient
- ESP8266WebServer
- OneWire
- DallasTemperature
- MQ135
- DFRobot_DHT11

**Setup:**
1. Connect the hardware components as per the provided pin mappings in the code.
2. Install the necessary libraries mentioned above.
3. Update the WiFi credentials (`ssid` and `password`) in the code to match your network.
4. Upload the code to the ESP8266 microcontroller using the Arduino IDE or another compatible platform.
5. Power up the system and ensure it connects to the WiFi network.

**Usage:**
1. Access the web interface by navigating to the ESP8266's IP address in a web browser.
2. Control the air purifier, fan, water pump, and Peltier module manually through the provided interface.
3. Monitor temperature, humidity, and air quality readings displayed on the web interface.
4. Utilize automatic control modes for the Peltier module based on temperature settings.
5. Interact with the system remotely from any device connected to the same network.

**Endpoints:**
- `/`: Displays the main web interface.
- `/apcontrol`: Control the air purifier.
- `/fancontrol`: Control the fan.
- `/waterpump`: Control the water pump.
- `/peltier`: Control the Peltier module.
- `/peltierauto`: Activate automatic mode for the Peltier module.
- `/peltierheat`: Activate heating mode for the Peltier module.
- `/peltiercold`: Activate cooling mode for the Peltier module.
- `/ppm`: Display air quality in parts per million (PPM).
- `/sens`: Display various sensor readings.

**Contributing:**
- Contributions and improvements to the codebase are welcome.
- Please submit any issues or suggestions through GitHub's issue tracker.

**Acknowledgements:**
- This project was inspired by various open-source projects and contributions from the community.

**Author:**
Johanth P S - johanth6600@gmail.com
