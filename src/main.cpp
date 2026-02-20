#include <iostream>
#include <cpr/cpr.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <map>

struct weatherForecast
{
    double Lowtemperature = 1000;
    double HighTemperature = -1000;
    std::string description;
};


int main() {
    std::ifstream file("../.env");
    std::string line;
    std::string apiKey;
    std::string city;
    std::map<std::string, weatherForecast> forecastMap;

    while (std::getline(file, line))
    {
        if (line.find("WEATHER_API_KEY") != std::string::npos) {
            apiKey = line.substr(line.find("=") + 1);
        }    
    }
    file.close();

    std::cout << "Enter city name: ";
    std::getline(std::cin, city);

    std::string url = "http://api.openweathermap.org/data/2.5/weather";
    cpr::Response getWeatherData = cpr::Get(
        cpr::Url{url},
        cpr::Parameters{
            {"q", city}, 
            {"appid", apiKey}, 
            {"units", "imperial"}}
    );
    std::string url2 = "http://api.openweathermap.org/data/2.5/forecast";
    cpr::Response getWeatherData2 = cpr::Get(
        cpr::Url{url2},
        cpr::Parameters{
            {"q", city}, 
            {"appid", apiKey}, 
            {"units", "imperial"}}
    );
    nlohmann::json jsonData2 = nlohmann::json::parse(getWeatherData2.text);
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

    nlohmann::json jsonData = nlohmann::json::parse(getWeatherData.text);
    std::cout << "City: " << jsonData["name"].get<std::string>() << std::endl;
    std::cout << "Temperature: " << jsonData["main"]["temp"].get<double>() << "°F" << std::endl;
    std::cout << "Description: " << jsonData["weather"][0]["description"].get<std::string>() << std::endl;
    std::cout << "Humidity: " << jsonData["main"]["humidity"].get<int>() << "%" << std::endl;
    std::cout << "Wind Speed: " << jsonData["wind"]["speed"].get<double>() << " m/s\n" << std::endl;
    
    for (auto& [date, forecast] : forecastMap) {
        std::cout << "Date: " << date << "\n";
        std::cout << "Low Temperature: " << forecast.Lowtemperature << "°F\n";
        std::cout << "High Temperature: " << forecast.HighTemperature << "°F\n";
        std::cout << "Description: " << forecast.description << "\n\n";
    }
    return 0;
}