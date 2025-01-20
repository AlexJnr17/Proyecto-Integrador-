#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA 100

typedef struct {
    float co2;
    float so2;
    float no2;
    float pm25;
    float temperature;
    float wind_speed;
    float humidity;
} AirData;

float weighted_average(float data[], int size) {
    float sum = 0.0, weight_sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += data[i] * (i + 1);
        weight_sum += (i + 1);
    }
    return sum / weight_sum;
}

void calculate_weighted_prediction(const AirData history[], int size) {
    float co2_levels[MAX_DATA];
    for (int i = 0; i < size; i++) {
        co2_levels[i] = history[i].co2;
    }
    float prediction = weighted_average(co2_levels, size);
    printf("Prediccion por promedios ponderados (CO2): %.2f\n", prediction);
}

int main() {
    AirData history[] = {
        {400, 50, 30, 20, 25.0, 10.0, 60.0},
        {420, 55, 35, 22, 26.0, 12.0, 65.0},
        {430, 60, 40, 23, 27.0, 14.0, 70.0}
    };
    int size = sizeof(history) / sizeof(history[0]);

    calculate_weighted_prediction(history, size);
    return 0;
}
