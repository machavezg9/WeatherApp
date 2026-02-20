#ifndef WEATHER_HPP
#define WEATHER_HPP

#include <string>
#include <cpr/cpr.h>

struct weatherForecast
{
    double Lowtemperature = 1000;
    double HighTemperature = -1000;
    std::string description;
};

std::string getAPIKey();
std::string getCityInput();
cpr::Response fetchWeatherData(const std::string& city, const std::string& apiKey);
cpr::Response fetchForecastData(const std::string& city, const std::string& apiKey);
std::string displayCurrentWeather(const cpr::Response& weatherResponse);
std::string displayForecast(const cpr::Response& forecastResponse);

#endif // WEATHER_HPP