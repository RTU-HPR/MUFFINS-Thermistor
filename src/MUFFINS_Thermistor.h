#include <Arduino.h>
#include <MUFFINS_Component_Base.h>

class Thermistor : public Component_Base
{
public:
  struct Config
  {
    int pin;
    int adc_resolution;
    double reference_resistance;
    double nominal_resistance;
    double nominal_temperature_kelvin; // Default is 25 C = 298.15 K
    double b_value;
  };

private:
  struct Data
  {
    double temperature;
  };

  /**
    Resistance to Kelvin conversion:
    1/K = 1/K0 + ln(R/R0)/B;
    K = 1 / (1/K0 + ln(R/R0)/B);
    Where
    K0 - nominal temperature,
    R0 - nominal resistance at a nominal temperature,
    R - the input resistance,
    B - b-value of a thermistor.

    @param resistance resistance value to convert
    @return temperature in degree Kelvin
  */
  double _resistance_to_kelvins(double resistance);

  /**
    Calculates a resistance of the thermistor:
    Converts a value of the thermistor sensor into a resistance.
    R = R0 / (ADC / V - 1);
    Where
    R0 - nominal resistance at a nominal temperature,
    ADC - analog port resolution (1023, for Arduino)
    V - current voltage (analog port value).

    @return resistance of the thermistor sensor.
  */
  double _read_resistance();

public:
  // Local config
  Config _config;

  // Data
  Data data;

  /**
   * @brief Construct a new Thermistor object
   */
  Thermistor(String component_name = "Thermistor", void (*info_function)(String) = nullptr, void (*error_function)(String) = nullptr);

  /**
   * @brief Destroy the Radio object
   */
  ~Thermistor();

  /**
   * @brief Begin the Thermistor
   *
   * @param config
   * @return true if the Thermistor was started successfully
   */
  bool begin(const Config &config);

  /**
   * @brief Read temperature
   */
  void read();
};
