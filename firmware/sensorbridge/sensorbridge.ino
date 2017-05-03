
#define SENSOR_COUNT 6
#define STATUS_LED_PIN 7

// Mapping of sensors to pins. The first value of the sensor pin arrays
// is the pin that Sensor1 is connected to, second value for Sensor2 and
// so on.
//                       Sensor id: 1, 2, 3, 4, 5, 6
uint8_t sensorDataPins[]        = { 5, 4, 3, 2, 0, 1 }; // Analog input pin the sensor is connected to
uint8_t sensorConnectionPins[]  = { 4, 5, 6, 7, 3, 2 }; // Digital input pin the sensor is connected to

void setup() {

  // Setup pin modes for the connection pins
  for (int i = 0; i < SENSOR_COUNT; i++) {
    pinMode(sensorConnectionPins[i], INPUT);
  }
  pinMode(STATUS_LED_PIN, OUTPUT);

  // Start serial communication
  Serial.begin(9600);
  
}

void loop() {

  // Read and communicate values
  for (int i = 0; i < SENSOR_COUNT; i++) {

    // Determine value of pin
    bool sensorConnected = digitalRead(sensorConnectionPins[i]);
    uint16_t value = sensorConnected ? analogRead(sensorDataPins[i]) : 65535;

    // Write value to serial port
    Serial.write(highByte(value));
    Serial.write(lowByte(value));
    
  }
  
  // Terminate series of values
  Serial.write(0x0D);
  Serial.write(0x0A);

  // Wait for a bit
  delay(20);
  
}

