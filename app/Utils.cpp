#include "Utils.h"

std::string Utils::acomodar(std::string texto) {
    /*
     * Pasamos el texto a minusculas (en caso de que se use una variable en mayúscula)
     */
    std::transform(texto.begin(), texto.end(), texto.begin(), [](unsigned char c) {
        return std::tolower(c); });

    /*
     * Truco para tokenizar negativos.
     * 
     * Reemplazar el menos por un más y un menos.
     */
    std::string polinomio = std::regex_replace(texto, std::regex("-"), "+-");

    /*
     * Se eliminan los espacios al polinomio
     */
    std::string::iterator it = std::remove(polinomio.begin(), polinomio.end(), ' ');
    polinomio.erase(it, polinomio.end());

    return polinomio;
}

std::vector<std::string> Utils::obtener_terminos(std::string polinomioStr) {
    std::vector<std::string> elementos;
    if (!polinomioStr.empty()) {

        char* str = new char[polinomioStr.size() + 1];
        strncpy(str, polinomioStr.c_str(), polinomioStr.size());

        char* token = strtok(str, "+");
        while (token != NULL) {
            std::string elemento = token;
            elementos.push_back(elemento);
            token = strtok(NULL, "+");
        }
        delete[] str;
    }
    return elementos;
}

Monomio Utils::str2Monomio(std::string texto) {
    Monomio mono;

    if (!texto.empty()) {
        std::string str = texto;
        std::size_t pos = str.find("x");

        //        std::cout << "Texto: " << texto << " Pos: " << pos << std::endl;
        if (pos != std::string::npos) {
            /// Coeficiente
            std::string coefStr = str.substr(0, pos);
            if (coefStr.empty()) {
                mono.SetCoeficiente(1);
            } else {
                mono.SetCoeficiente(atof(coefStr.c_str()));
            }

            /// Grado
            unsigned int resto = pos + 3;
            if (str.size() >= resto) {
                std::string gradoStr = str.substr(resto, str.size() - 1);
                mono.SetGrado(atof(gradoStr.c_str()));
            } else if (str.size() > pos) {
                mono.SetGrado(1);
            } else {
                mono.SetGrado(0);
            }
        } else {
            mono.SetCoeficiente(atof(str.c_str()));
            mono.SetGrado(0);
        }
    }
    return mono;
}

std::vector<Monomio> Utils::convertir(std::string polinomioStr) {
    std::vector<Monomio> listado;
    if (!polinomioStr.empty()) {
        std::string resultado = acomodar(polinomioStr);
        std::vector<std::string> terminos = obtener_terminos(resultado);

        std::vector<int>::size_type i = 0;
        std::vector<Monomio> polinomio;

        for (i = 0; i < terminos.size(); i++) {
            std::string valor = terminos[i];
            Monomio monomio = str2Monomio(valor);
            polinomio.push_back(monomio);
        }
        listado = polinomio;
    }
    return listado;
}

/**
 * Funcion para calcular las raices de una funcion
 * aplicando el metodo de Newton-Raphson
 * @param polinomio: Arreglo de Monomios
 * @return El valor de la solucion
 */
double Utils::evaluar(std::vector<Monomio> polinomio) {
    // 1. Calculo de la derivada de la funcion original (del polinomio)
    std::vector<Monomio> derivada;

    std::cout << "Derivada: ";
    std::vector<Monomio>::size_type i;
    for (i = 0; i < polinomio.size(); i++) {
        Monomio monomio = polinomio[i];
        Monomio derivadaMonomio;

        derivadaMonomio.SetCoeficiente(monomio.GetGrado() * monomio.GetCoeficiente());
        derivadaMonomio.SetGrado(monomio.GetGrado() - 1);

        derivada.push_back(derivadaMonomio);
        std::cout << derivadaMonomio.GetCoeficiente() << "x^" << derivadaMonomio.GetGrado() << " ";
    }
    std::cout << std::endl;

    // 2. Pivote = x0 (primera aproximacion)
    double pivote = 1;
    double error  = 0.01;
    double xn     = pivote;
    double xn_1   = 0.0;

    // 3. Evaluacion del pivote en la funcion original
    while (xn - xn_1 > error) {
        double resultadoPolinomio;
        std::vector<Monomio>::size_type k;
        double sumaP = (double) 0;
        for (k = 0; k < polinomio.size(); k++) {
            Monomio monomioP = polinomio[k];
            std::cout << "iteracion" << k << std::endl;
            std::cout << "--> Coeficiente Polinomio:" << monomioP.GetCoeficiente() << std::endl;
            std::cout << "--> Grado Polinomio:" << monomioP.GetGrado() << std::endl << std::endl;
            sumaP += (monomioP.GetCoeficiente() * pow(pivote, monomioP.GetGrado()));
        }
        resultadoPolinomio = sumaP;
        std::cout << "--> Resultado Polinomio: " << resultadoPolinomio << std::endl;

        // 4. Evaluacion del pivote en la funcion derivada
        double resultadoDerivada;
        std::vector<Monomio>::size_type j;
        double sumaD = (double) 0;
        for (j = 0; j < derivada.size(); j++) {
            Monomio monomio = derivada[j];
            sumaD += (monomio.GetCoeficiente() * pow(pivote, monomio.GetGrado()));
        }
        resultadoDerivada = sumaD;
        std::cout << "--> Resultado Derivada: " << resultadoDerivada << std::endl;

        // 5. Calculo del nuevo punto (pivote): xn - f(Xn)/f'(Xn)
        pivote = pivote - resultadoPolinomio/resultadoDerivada;
    }

    // 6. Itera desde el paso 3

    return pivote;
}
