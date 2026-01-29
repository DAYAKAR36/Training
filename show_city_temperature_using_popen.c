 // Get temperature of a city from an api and display it.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "weather.dat"
#define GET_TOKEN strtok(NULL, "{},\":");

void remove_new_line(char*);

void main() 
{
    char city_name[50];
    float temperature = -1000.0;
    printf("Enter the city name to get temperature: ");
    fgets(city_name, sizeof(city_name), stdin);
    remove_new_line(city_name);
    char command[200];
    sprintf(command, "curl -s \"https://api.openweathermap.org/data/2.5/weather?q=%s&appid=35fcf43fe03b83f3ee39a112e3a64194&units=metric\"", city_name);
    char weather_details[1000];
    FILE *fp_weather = popen(command, "r");
    fread(weather_details, sizeof(weather_details), 1, fp_weather);
    pclose(fp_weather);
    char *token = strtok(weather_details, "{},\":");
    while (token != NULL) 
    {
        if (strcmp(token, "city not found") == 0)
        {
            printf("%s", token);
            return;
        }
        if (strcmp(token, "temp") == 0)
        {
            token = GET_TOKEN;
            temperature = atof(token);
            break;
        }
        token = GET_TOKEN;
    }
    if (temperature == -1000)
    {
        printf("Failed to load the %s weather details.\n", city_name);
    }
    else
    {
        printf("Temperature of %s is %.2f degrees.", city_name, temperature);
    }
}
