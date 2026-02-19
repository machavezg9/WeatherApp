#include <iostream>
#include <cpr/cpr.h>
#include <fstream>
#include <nlohmann/json.hpp>


int main() {
    std::ifstream file("../.env");
    std::string line;
    std::string apiKey;

    while (std::getline(file, line))
    {
        if (line.find("WEATHER_API_KEY") != std::string::npos) {
            apiKey = line.substr(line.find("=") + 1);
        }    
    }
    file.close();

    std::string url = "http://api.openweathermap.org/data/2.5/weather?q=London&appid=" + apiKey;
    cpr::Response getWeatherData = cpr::Get(cpr::Url{url});    
    std::cout << getWeatherData.status_code << std::endl;
    std::cout << getWeatherData.text << std::endl;
    return 0;
}