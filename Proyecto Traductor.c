#include <iostream>
#include <map>
#include <string>

using namespace std;

// Diccionario básico de traducciones
map<string, string> spanishToEnglish = {
    {"hola", "hello"},
    {"adios", "goodbye"},
    {"gracias", "thank you"},
    {"por favor", "please"},
    {"si", "yes"},
    {"no", "no"}
};

void mostrarMenu() {
    cout << "\n--- Traductor en C++ ---\n";
    cout << "1. Traducir palabra de Español a Inglés\n";
    cout << "2. Agregar nueva traducción\n";
    cout << "3. Salir\n";
    cout << "Seleccione una opción: ";
}

void traducirPalabra() {
    string palabra;
    cout << "Ingrese una palabra en español: ";
    cin >> palabra;

    if (spanishToEnglish.find(palabra) != spanishToEnglish.end()) {
        cout << "Traducción: " << spanishToEnglish[palabra] << endl;
    } else {
        cout << "La palabra no está en el diccionario.\n";
    }
}

void agregarTraduccion() {
    string palabraEsp, palabraIng;
    cout << "Ingrese la palabra en español: ";
    cin >> palabraEsp;
    cout << "Ingrese la traducción en inglés: ";
    cin >> palabraIng;

    spanishToEnglish[palabraEsp] = palabraIng;
    cout << "Nueva traducción agregada con éxito.\n";
}

int main() {
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                traducirPalabra();
                break;
            case 2:
                agregarTraduccion();
                break;
            case 3:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida, intente de nuevo.\n";
        }
    } while (opcion != 3);

    return 0;
}

//Test kevin
