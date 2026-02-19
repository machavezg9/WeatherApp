# WeatherApp

A terminal-based C++ application that pulls weather data from the OpenWeatherMap API. Built as a learning project to practice C++ development, API calls, and JSON parsing.

## Prerequisites

- g++ (C++ compiler)
- CMake
- Git

## Setup

### 1. Install vcpkg (C++ package manager)

```bash
cd ~
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
```

### 2. Install required libraries

```bash
cd ~/vcpkg
./vcpkg install cpr
./vcpkg install nlohmann-json
```

- **cpr** — HTTP client library for making API requests
- **nlohmann-json** — JSON parsing library

### 3. Clone the repository

```bash
git clone https://github.com/YOUR_USERNAME/WeatherApp.git
cd WeatherApp
```

### 4. Create the build directory

```bash
mkdir build
```

### 5. Configure your API key

Create a `.env` file in the project root:

```bash
touch .env
```

Add your OpenWeatherMap API key to the `.env` file:

```
WEATHER_API_KEY=your_api_key_here
```

You can get a free API key at [https://openweathermap.org/](https://openweathermap.org/)

> **Note:** The `.env` file is excluded from version control via `.gitignore` to keep your API key secure.

## Project Structure

```
WeatherApp/
├── src/            # Source code (.cpp files)
│   └── main.cpp    # Application entry point
├── include/        # Header files (.hpp files)
│   └── config.hpp  # Configuration and environment loading
├── build/          # Compiled output (not tracked by Git)
├── .env            # API key storage (not tracked by Git)
├── .gitignore      # Git exclusion rules
├── CMakeLists.txt  # Build configuration
└── README.md
```
