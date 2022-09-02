#include "Utils.h"
#include <cstdlib>
#include <iostream>
#include <string>


/**
 * Función que muestra los participantes del grupo
 * @param programa nombre del ejecutable
 */
void participantes(std::string programa) {
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
	if (argc == 3) {
		// Procede a hacer el calculo si la cantidad de parametros es correcta
		const std::string polinomio(argv[1]);
		const double valor = std::atof(argv[2]);
		std::cout << std::endl << "polinomio (cmd): " << polinomio << std::endl;
		std::cout << "Valor: " << valor << std::endl;

		std::cout << "polinomio (convertido): ";
		std::vector<Monomio> monomios = Utils::convertir(polinomio);
		std::vector<Monomio>::size_type i = 0;
		for (i = 0; i < monomios.size(); i++) {
			Monomio monomio = monomios[i];
			std::cout << monomio.GetCoeficiente() << "x^" << monomio.GetGrado() << " ";
		}
		std::cout << std::endl;

		double resultado = Utils::evaluar(monomios, valor);
		std::cout << "Resultado: " << resultado << std::endl;
	} else {
		// Muestra los integrantes
		participantes(argv[0]);
	}
	return EXIT_SUCCESS;
}
