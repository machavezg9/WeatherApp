#include "../include/weather.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <iomanip>


std::string getAPIKey() {
    std::string apiKey;
    std::ifstream envFile("../.env");
    if (envFile.is_open()) {
        std::string line;
        while (std::getline(envFile, line)) {
            if (line.find("WEATHER_API_KEY=") == 0) {
                apiKey = line.substr(16); // Extract the API key value
                break;
            }
        }
        envFile.close();
    } else {
        std::cerr << "Unable to open .env file. Please ensure it exists and contains the WEATHER_API_KEY." << std::endl;
    }
    return apiKey;
}

std::string getCityInput() {
    std::string city;
    std::cout << "Enter city name: ";
    std::getline(std::cin, city);
    return city;
}

cpr::Response fetchWeatherData(const std::string& city, const std::string& apiKey) {
    std::string url = "http://api.openweathermap.org/data/2.5/weather";
    cpr::Response response = cpr::Get(
        cpr::Url{url},
        cpr::Parameters{
            {"q", city}, 
            {"appid", apiKey}, 
            {"units", "imperial"}
        }
    );
    return response;
}

cpr::Response fetchForecastData(const std::string& city, const std::string& apiKey) {
    std::string url = "http://api.openweathermap.org/data/2.5/forecast";
    cpr::Response response = cpr::Get(
        cpr::Url{url},
        cpr::Parameters{
            {"q", city}, 
            {"appid", apiKey}, 
            {"units", "imperial"}
        }
    );
    return response;
}

std::string displayCurrentWeather(const cpr::Response& weatherResponse) {
    nlohmann::json jsonData = nlohmann::json::parse(weatherResponse.text);
    std::string cityName = jsonData["name"];
    double temperature = jsonData["main"]["temp"];
    std::string description = jsonData["weather"][0]["description"];
    int humidity = jsonData["main"]["humidity"]; 
    double windSpeed = jsonData["wind"]["speed"];

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    oss << "\nCurrent weather in " << cityName << "\nDescription: " << description << "\nTemperature: " << temperature << "°F";
    oss << "\nHumidity: " << humidity << "%\nWind Speed: " << windSpeed << " mph\n";
    return oss.str();
}

std::string displayForecast(const cpr::Response& forecastResponse) {
    std::map<std::string, weatherForecast> forecastMap;
    nlohmann::json jsonData2 = nlohmann::json::parse(forecastResponse.text);
    for (int i = 0; i < jsonData2["list"].size(); ++i) {
        std::string dateTime = jsonData2["list"][i]["dt_txt"].get<std::string>().substr(0, 10);
        std::string time = jsonData2["list"][i]["dt_txt"].get<std::string>().substr(11, 8);
        double temp = jsonData2["list"][i]["main"]["temp"].get<double>();
        std::string description = jsonData2["list"][i]["weather"][0]["description"].get<std::string>();

        if (forecastMap.find(dateTime) == forecastMap.end()) {
            forecastMap[dateTime] = weatherForecast{temp, temp, description};
        } else {
            if (temp < forecastMap[dateTime].Lowtemperature) {
                forecastMap[dateTime].Lowtemperature = temp;
            }
            if (temp > forecastMap[dateTime].HighTemperature) {
                forecastMap[dateTime].HighTemperature = temp;
            }
            if (time == "12:00:00" || time == "15:00:00") {
                forecastMap[dateTime].description = description;
            }
        }
    }        
    std::ostringstream oss;
    for (const auto& [date, forecast] : forecastMap) {
        oss << "Date: " << date << "\n";
        oss << "Low Temperature: " << std::fixed << std::setprecision(1) << forecast.Lowtemperature << "°F\n";
        oss << "High Temperature: " << std::fixed << std::setprecision(1) << forecast.HighTemperature << "°F\n";
        oss << "Description: " << forecast.description << "\n\n";
    }
    return oss.str();
}
