// Street Light Control using LDR
// LDR -> A5, Light -> Pin 3

const int LDR_PIN = A5;     // LDR input pin
const int LIGHT_PIN = 3;    // Light output pin
int ldrValue = 0;           // Variable to store LDR reading
const int THRESHOLD = 512;  // Brightness threshold (0-1023)

void setup() {
  pinMode(LIGHT_PIN, OUTPUT);
  Serial.begin(9600);

  // Initial message
  Serial.println("Street Light Control System Initialized");
}

void loop() {
  // Read the LDR sensor value
  ldrValue = analogRead(LDR_PIN);

  // Display the raw value
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Compare with threshold
  if (ldrValue > THRESHOLD) {
    digitalWrite(LIGHT_PIN, LOW);   // Turn OFF light
    Serial.println("Street light OFF");
  } else {
    digitalWrite(LIGHT_PIN, HIGH);  // Turn ON light
    Serial.println("Street light ON");
  }

  delay(200); // Small delay for stability
}
