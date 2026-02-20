#include "../include/weather.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

int main() {
    std::string apiKey = getAPIKey();
    if (apiKey.empty()) {
        std::cerr << "API key is missing. Please add your WEATHER_API_KEY to the .env file." << std::endl;
        return 1;
    }

    do {
        std::string city = getCityInput();
        if (city == "quit" || city == "exit") {
            std::cout << "Exiting the application. Goodbye!" << std::endl;
            break;
        }
        
        if (city.empty()) {
            std::cerr << "City name cannot be empty. Please try again." << std::endl;
            continue;
        }

        cpr::Response weatherResponse = fetchWeatherData(city, apiKey);
        cpr::Response forecastResponse = fetchForecastData(city, apiKey);

        if (weatherResponse.status_code != 200) {
            std::cerr << "Failed to retrieve weather data for " << city << ". Please check the city name and try again." << std::endl;
            continue;
        }
        if (forecastResponse.status_code != 200) {
            std::cerr << "Failed to retrieve forecast data for " << city << ". Please check the city name and try again." << std::endl;
            continue;
        }
        try {
            std::cout << displayCurrentWeather(weatherResponse) << std::endl;
        } catch (const nlohmann::json::exception& e) {
            std::cerr << "Failed to parse current weather data: " << e.what() << std::endl;
            continue;
        }
        try {
            std::cout << displayForecast(forecastResponse) << std::endl;
        } catch (const nlohmann::json::exception& e) {
            std::cerr << "Failed to parse forecast data: " << e.what() << std::endl;
            continue;
        }

    } while (true);    
    return 0;
}