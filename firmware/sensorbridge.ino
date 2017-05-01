uint16_t sensorValues[] = {0, 0, 0, 0, 0, 0};
float valueSeed = 0.0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  // Capture values
  sensorValues[0] = wrapAround(sensorValues[0] + 1, 0, 1023);
  sensorValues[1] = wrapAround(sensorValues[1] - 1, 0, 1023);
  sensorValues[2] = wrapAround(sensorValues[2] + 10, 0, 1023);
  sensorValues[3] = wrapAround(sensorValues[3] - 10, 0, 1023);
  sensorValues[4] = (uint16_t) (512 + (sin(valueSeed += 0.05) * 511.0));
  sensorValues[5] = analogRead(5);
  
  // Output values
  for (int i = 0; i < 6; i++) {
    uint16_t v = sensorValues[i];
    Serial.write(highByte(v));
    Serial.write(lowByte(v));
  }
  Serial.println();

  delay(20);
  
}

int wrapAround(int v, int min, int max) {
  if (v < min) {
    return max - (min - v);
  } else if (v > max) {
    return v - max;
  } else {
    return v;
  }
}

