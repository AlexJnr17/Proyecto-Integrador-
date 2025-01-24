#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 100
#define MAX_REGION_NAME 50

typedef struct {
    float co2;
    float so2;
    float no2;
    float pm25;
    float temperature;
    float wind_speed;
    float humidity;
} AirData;

void linear_regression(const float x[], const float y[], int n, float *m, float *b) {
    float sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0;
    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }
    float denominator = (n * sum_x2 - sum_x * sum_x);
    if (denominator == 0) {
        *m = 0;
        *b = 0;
    } else {
        *m = (n * sum_xy - sum_x * sum_y) / denominator;
        *b = (sum_y - (*m) * sum_x) / n;
    }
}

void predict_new_values(float m, float b, const float new_temps[], int size, const char *filename, const char *region) {
    FILE *file = fopen(filename, "a"); 
    if (!file) {
        printf("Error al abrir el archivo para escribir las predicciones.\n");
        return;
    }

    fprintf(file, "\nPredicciones de CO2 para la region: %s\n", region);
    printf("Predicciones de CO2 para la region: %s\n", region);
    for (int i = 0; i < size; i++) {
        float predicted_co2 = m * new_temps[i] + b;
        fprintf(file, "Temp: %.2f -> CO2: %.2f\n", new_temps[i], predicted_co2);
        printf("Temp: %.2f -> CO2: %.2f\n", new_temps[i], predicted_co2);
    }

    fclose(file);
    printf("Las predicciones para la region %s se han guardado en el archivo: %s\n", region, filename);
}

void calculate_regression_prediction(const AirData history[], int size, const char *region) {
    if (size < 2) {
        printf("Error: Se necesitan al menos dos datos para realizar la regresión lineal.\n");
        return;
    }

    float co2_levels[MAX_DATA], temp_levels[MAX_DATA];
    for (int i = 0; i < size; i++) {
        co2_levels[i] = history[i].co2;
        temp_levels[i] = history[i].temperature;
    }

    float m, b;
    linear_regression(temp_levels, co2_levels, size, &m, &b);
    printf("Prediccion por regresion lineal (CO2 vs Temp) para la region %s: y = %.2fx + %.2f\n", region, m, b);

    float new_temps[3];

    if (strcmp(region, "sierra") == 0) {
        new_temps[0] = 10.0;
        new_temps[1] = 12.0;
        new_temps[2] = 15.0;
    } else if (strcmp(region, "costa") == 0) {
        new_temps[0] = 28.0;
        new_temps[1] = 30.0;
        new_temps[2] = 32.0;
    } else if (strcmp(region, "amazonia") == 0) {
        new_temps[0] = 24.0;
        new_temps[1] = 26.0;
        new_temps[2] = 27.0;
    } else {
        printf("Ingrese tres nuevas temperaturas para la region %s: ", region);
        for (int i = 0; i < 3; i++) {
            scanf("%f", &new_temps[i]);
        }
    }

    predict_new_values(m, b, new_temps, 3, "predicciones.txt", region);
}

void input_data(AirData history[], int *size) {
    printf("Ingrese el numero de datos a registrar: ");
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Ingrese los datos para el registro %d (CO2, Temp): ", i + 1);
        scanf("%f %f", &history[*size].co2, &history[*size].temperature);
        (*size)++;
    }
}

int main() {
    AirData history[] = {
        {400, 50, 30, 20, 25.0, 10.0, 60.0},
        {420, 55, 35, 22, 26.0, 12.0, 65.0},
        {430, 60, 40, 23, 27.0, 14.0, 70.0}
    };
    int size = sizeof(history) / sizeof(history[0]);

    char region[MAX_REGION_NAME];
    printf("Seleccione una region (sierra, costa, amazonia) o escriba 'otra' para ingresar nueva informacion: ");
    scanf("%s", region);

    if (strcmp(region, "otra") == 0) {
        printf("Ingrese el nombre de la nueva region o lugar: ");
        scanf("%s", region);
        input_data(history, &size);
    }

    calculate_regression_prediction(history, size, region);
    return 0;
}
