#include <iostream>
#include <string>

int main() {
    std::cout << "El programa realiza los principales estadísticos de una muestra" << std::endl;
    int n_datos;
    double media, mediana, recorrido, recorrido_intercuartilico, varianza;
    double desviacion_tipica, cuasivarianza, cuasidesviacion_tipica, cv;
    std::cout << "Introduzca la cantidad de datos de la muestra: ";
    std::cin >> n_datos;

    std::cout << "Media: " << media << std::endl;
    std::cout << "Mediana: " << mediana << std::endl;
    std::cout << "Recorrido: " << recorrido << std::endl;
    std::cout << "Recorrido intercuartilico: " << recorrido_intercuartilico << std::endl;
    std::cout << "Varianza: " << varianza << std::endl;
    std::cout << "Desviacion tipica: " << desviacion_tipica << std::endl;
    std::cout << "Cuasivarianza: " << cuasivarianza << std::endl;
    std::cout << "Cuasidesviacion tipica: " << cuasidesviacion_tipica << std::endl;
    std::cout << "Coeficiente de Pearson: " << cv << std::endl;
    return 0;
}
