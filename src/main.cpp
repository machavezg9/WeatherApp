#include <iostream>
#include <cpr/cpr.h>
#include <fstream>
#include <nlohmann/json.hpp>


int main() {
    std::ifstream file("../.env");
    std::string line;
    std::string apiKey;
    std::string city;

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
            {"units", "metric"}}
    );

    nlohmann::json jsonData = nlohmann::json::parse(getWeatherData.text);
    std::cout << "City: " << jsonData["name"].get<std::string>() << std::endl;
    std::cout << "Temperature: " << jsonData["main"]["temp"].get<double>() << "°C" << std::endl;
    std::cout << "Description: " << jsonData["weather"][0]["description"].get<std::string>() << std::endl;
    std::cout << "Humidity: " << jsonData["main"]["humidity"].get<int>() << "%" << std::endl;
    std::cout << "Wind Speed: " << jsonData["wind"]["speed"].get<double>() << " m/s" << std::endl;
    return 0;
}