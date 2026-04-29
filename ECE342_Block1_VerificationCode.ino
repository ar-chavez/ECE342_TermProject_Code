const int ldrPin = 32;       // Pin on ESP32
const float R2 = 47000.0;    
const float V_supply = 3.3;  // Power supply voltage [SET EQUAL TO POWER SUPPLY VOLTAGE]

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // Sets ADC range from 0 to 4095
}

void loop() {
  int adcValue = analogRead(ldrPin);

  // Converts ADC to Voltage at the junction (Vph)
  float Vph = adcValue * (3.3 / 4095.0);
  
  // Calculates voltage across the 47k resistor (V_R2)
  float VR2 = V_supply - Vph;

  // Calculate Current in uA
  float current_uA = (VR2 / R2) * 1000000.0;

  // Calculate Photoresistor Resistance (Rph)
  float Rph = 0;
  if (Vph < V_supply && Vph > 0) {
    Rph = R2 * (Vph / (V_supply - Vph));
  }


  // --- OUTPUT FOR SERIAL PLOTTER ---
  // Line 1 = Resistance (Ohms), Line 2 = Current (uA)
  Serial.print("Resistance_Ohms:");
  Serial.print(Rph);
  Serial.print(",");
  
  Serial.print("Current_uA:");
  Serial.println(current_uA);

  // Sampling delay (e.g., 4 = 4ms)
  // Use 4ms to sample to measure increase/decreamse time for resistance changes
  // Use 250ms to show current through circuit (not required, but easier to read)
  delay(4); 
}