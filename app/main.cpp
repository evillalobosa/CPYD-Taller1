#include "Utils.h"
#include <cstdlib>
#include <iostream>
#include <string>


/**
 * Función que muestra los participantes del grupo
 */
void participantes() {
	std::cout << std::endl << "=== Taller 01: Integrantes ===";
	std::cout << std::endl << "- Julio Aceituno Zalaya (jaceituno@utem.cl)";
	std::cout << std::endl << "- Enrique Villalobos (evillalobos@utem.cl)";
	std::cout << std::endl << "- Oliver Chacón Álvarez (oliver.chacona@utem.cl)" << std::endl;
}


/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */
int main(int argc, char** argv) {
	if (argc == 2) {
		// Procede a hacer el calculo si la cantidad de parametros es correcta
		const std::string polinomio(argv[1]);
		std::cout << "Polinomio: ";
		std::vector<Monomio> monomios = Utils::convertir(polinomio);

		// Muestra el Polinomio ingresado
		std::vector<Monomio>::size_type i = 0;
		for (i = 0; i < monomios.size(); i++) {
			Monomio monomio = monomios[i];
			std::cout << monomio.GetCoeficiente() << "x^" << monomio.GetGrado() << " ";
		}
		std::cout << std::endl;

		// Calcula la solucion del polinomio
		double resultado = Utils::evaluar(monomios);
		std::cout << "Resultado: " << resultado << std::endl;
	} else {
		// Muestra los integrantes
		participantes();
	}
	return EXIT_SUCCESS;
}
