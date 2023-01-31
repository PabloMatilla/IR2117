#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    std::cout << "El programa realiza los principales estadísticos de una muestra" << std::endl;
    int n_datos;
    std::vector<double> vector;
    double media, mediana, recorrido, varianza;
    double desviacion_tipica, cuasivarianza, cuasidesviacion_tipica, cv;
    std::cout << "Introduzca la cantidad de datos de la muestra: ";
    std::cin >> n_datos;
    for (int i = 0; i < n_datos; i++) {
        double dato;
        std::cout << "Introduzca el dato (" << i +1 << "): ";
        std::cin >> dato;
        vector.push_back(dato);
    }
    // Calculo de la media
    for (int i = 0; i < n_datos; i++) {
        media += vector[i];
    }
    media = media/n_datos;

    // Calculo de la mediana
    std::sort(vector.begin(), vector.end());
    if (n_datos % 2 == 0) {
        mediana = (vector[n_datos/2 -1] + vector[n_datos/2])/2;
    } else {
        mediana = vector[(n_datos)/2];
    }

    // Calculo de recorrido
    recorrido = vector[n_datos -1] - vector[0];

    // Calculo de varianza
    for (int i = 0; i < n_datos; i++) {
        varianza = std::pow(vector[i], 2);
    }
    varianza = varianza/2 - std::pow(media, 2);

    // Calculo de desviación tipica
    desviacion_tipica = std::pow(varianza, 0.5);

    std::cout << "Media: " << media << std::endl;
    std::cout << "Mediana: " << mediana << std::endl;
    std::cout << "Recorrido: " << recorrido << std::endl;
    std::cout << "Varianza: " << varianza << std::endl;
    std::cout << "Desviacion tipica: " << desviacion_tipica << std::endl;
    std::cout << "Cuasivarianza: " << cuasivarianza << std::endl;
    std::cout << "Cuasidesviacion tipica: " << cuasidesviacion_tipica << std::endl;
    std::cout << "Coeficiente de Pearson: " << cv << std::endl;
    return 0;
}
