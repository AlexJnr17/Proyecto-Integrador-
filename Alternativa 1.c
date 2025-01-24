#include <stdio.h>
#include <string.h>

#define ROWS 2 
#define COLS 7  
#define MAX_REGION_NAME 50

double weighted_average(double values[], double weights[], int size) {
    double total_weight = 0;
    double weighted_sum = 0;
    for (int i = 0; i < size; i++) {
        total_weight += weights[i];
        weighted_sum += values[i] * weights[i];
    }
    return total_weight != 0 ? weighted_sum / total_weight : 0;
}

void calculate_weighted_prediction(double history[ROWS][COLS], int rows, int cols, double predictions[], const char *region, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Error al abrir el archivo para guardar las predicciones.\n");
        return;
    }

    fprintf(file, "Predicciones para la region: %s\n", region);
    printf("Predicciones para la region: %s\n", region);

    for (int i = 0; i < rows; i++) {
        double weights[COLS];

        // Ajustar los pesos dependiendo de la región
        if (strcmp(region, "sierra") == 0) {
            for (int j = 0; j < cols; j++) {
                weights[j] = (j + 1) * 1.5; // Pesos más altos
            }
        } else if (strcmp(region, "costa") == 0) {
            for (int j = 0; j < cols; j++) {
                weights[j] = (j + 1) * 1.2; // Pesos moderados
            }
        } else if (strcmp(region, "amazonia") == 0) {
            for (int j = 0; j < cols; j++) {
                weights[j] = (j + 1) * 1.1; // Pesos ligeramente ajustados
            }
        } else {
            for (int j = 0; j < cols; j++) {
                weights[j] = j + 1; // Pesos predeterminados
            }
        }

        predictions[i] = weighted_average(history[i], weights, cols);
        fprintf(file, "Conjunto %d: %.2f\n", i + 1, predictions[i]);
        printf("Conjunto %d: %.2f\n", i + 1, predictions[i]);
    }

    fclose(file);
    printf("Resultados guardados en el archivo: %s\n", filename);
}

void input_data(double history[ROWS + 10][COLS], int *rows, int cols) {
    printf("Ingrese el numero de conjuntos de datos: ");
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Ingrese los valores para el conjunto %d (se requieren %d valores):\n", i + 1, cols);
        for (int j = 0; j < cols; j++) {
            scanf("%lf", &history[*rows][j]);
        }
        (*rows)++;
    }
}

void set_region_data(const char *region, double history[ROWS + 10][COLS], int *rows) {
    if (strcmp(region, "sierra") == 0) {
        history[0][0] = 420; history[0][1] = 60; history[0][2] = 35; history[0][3] = 25; history[0][4] = 22.0; history[0][5] = 15.0; history[0][6] = 65.0;
        history[1][0] = 410; history[1][1] = 55; history[1][2] = 32; history[1][3] = 22; history[1][4] = 21.0; history[1][5] = 14.0; history[1][6] = 60.0;
        *rows = 2;
    } else if (strcmp(region, "costa") == 0) {
        history[0][0] = 390; history[0][1] = 45; history[0][2] = 25; history[0][3] = 20; history[0][4] = 28.0; history[0][5] = 10.0; history[0][6] = 70.0;
        history[1][0] = 400; history[1][1] = 50; history[1][2] = 30; history[1][3] = 18; history[1][4] = 27.0; history[1][5] = 11.0; history[1][6] = 65.0;
        *rows = 2;
    } else if (strcmp(region, "amazonia") == 0) {
        history[0][0] = 440; history[0][1] = 65; history[0][2] = 40; history[0][3] = 30; history[0][4] = 26.0; history[0][5] = 12.0; history[0][6] = 75.0;
        history[1][0] = 430; history[1][1] = 60; history[1][2] = 38; history[1][3] = 28; history[1][4] = 25.0; history[1][5] = 13.0; history[1][6] = 72.0;
        *rows = 2;
    }
}

int main() {
    double history[ROWS + 10][COLS] = {0};
    int current_rows = 0;
    double predictions[ROWS + 10]; 

    char region[MAX_REGION_NAME];
    printf("Seleccione una region (sierra, costa, amazonia) o escriba 'otra' para ingresar nueva informacion: ");
    scanf("%s", region);

    if (strcmp(region, "otra") == 0) {
        printf("Ingrese el nombre de la nueva region o lugar: ");
        scanf("%s", region);
        input_data(history, &current_rows, COLS);
    } else {
        set_region_data(region, history, &current_rows);
    }

    calculate_weighted_prediction(history, current_rows, COLS, predictions, region, "predicciones_regiones.txt");

    return 0;
}
