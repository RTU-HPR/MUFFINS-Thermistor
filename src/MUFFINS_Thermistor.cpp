#include <MUFFINS_Thermistor.h>

Thermistor::Thermistor(String component_name, void (*info_function)(String), void (*error_function)(String)) : Component_Base(component_name, info_function, error_function)
{
  return;
}

Thermistor::~Thermistor()
{
  return;
}

double Thermistor::_resistance_to_kelvins(const double resistance)
{
  const double inverse_kelvin = 1.0 / _config.nominal_temperature_kelvin +
                                log(resistance / _config.nominal_resistance) / _config.b_value;
  return (1.0 / inverse_kelvin);
}

double Thermistor::_read_resistance()
{
  return _config.reference_resistance / (_config.adc_resolution / analogRead(_config.pin) - 1);
}

bool Thermistor::begin(const Config &config)
{
  _config = config;

  if (_config.pin < 0)
  {
    error("Pin is not set");
    return false;
  }

  if (_config.reference_resistance <= 0)
  {
    error("Reference resistance is not set");
    return false;
  }

  if (_config.nominal_resistance <= 0)
  {
    error("Nominal resistance is not set");
    return false;
  }

  if (_config.nominal_temperature_kelvin <= 0)
  {
    error("Nominal temperature is not set");
    return false;
  }

  if (_config.b_value >= 0)
  {
    error("B-value is not set");
    return false;
  }

  if (_config.adc_resolution <= 0)
  {
    error("ADC resolution is not set");
    return false;
  }

  pinMode(_config.pin, INPUT);

  info("Successfully started");
  set_initialized(true);

  return true;
}

void Thermistor::read()
{
  if (!initialized())
  {
    return;
  }

  double resistance = _read_resistance();
  double kelvin = _resistance_to_kelvins(resistance);
  data.temperature = kelvin - 273.15;
}