#include <Arduino.h>
#include <MUFFINS_Thermistor.h>

Thermistor thermistor;

Thermistor::Config thermistor_config = {
  .pin = 27,
  .adc_resolution = 4095,
  .reference_resistance = 10000,
  .nominal_resistance = 10000,
  .nominal_temperature_kelvin = 298.15,
  .b_value = -4050
};

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(1000);
  }

  // Set the ADC resolution to 12 bits
  analogReadResolution(12);

  thermistor.begin(thermistor_config);
}

void loop()
{
  thermistor.read();

  Serial.print("Temperature: ");
  Serial.print(thermistor.data.temperature);
  Serial.println(" C");

  delay(100);
}