#include <iostream>
#include <string>
#include <limits>
#include <direct.h>
#include <windows.h>
#include <fstream>
#include <cstdint>
#include <vector>
#include <map>
#include <cstdlib>

using namespace std;
int mostrarMenuUsuario();
void limpiarPantalla();
void pausar();
void traduccionOffline(const string& nombreUsuario);
bool registrarTraduccion(const string& nombreUsuario, const string& palabraOrigen,
                        const string& palabraDestino, const string& idiomaOrigen,
                        const string& idiomaDestino);

// Constantes para los idiomas
const vector<string> IDIOMAS = {"Deutsch", "English", "espa�ol", "Fran�ais", "italiano"};
const string RUTA_BASE = "D:\\College Shit\\U shit\\Progra III\\Proyecto Final Final\\";

// Funci�n para cargar palabras de un archivo
vector<string> cargarPalabras(const string& idioma) {
    vector<string> palabras;
    ifstream archivo(RUTA_BASE + idioma + ".txt");
    string palabra;

    if (archivo.is_open()) {
        while (getline(archivo, palabra)) {
            palabras.push_back(palabra);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo: " << idioma << ".txt" << endl;
    }

    return palabras;
}

// Funci�n para mostrar el men� de selecci�n de idioma
int seleccionarIdioma(const string& mensaje) {
    int opcion;
    cout << mensaje << endl;
    for (int i = 0; i < IDIOMAS.size(); i++) {
        cout << i + 1 << ". " << IDIOMAS[i] << endl;
    }
    cout << "Seleccione una opci�n: ";
    cin >> opcion;
    return opcion - 1; // Restamos 1 para que coincida con el �ndice del vector
}

//Funci�n para reproducci�n de audio
void reproducirAudio(const string& texto, const string& idioma) {
    string comando = "espeak -v " + idioma + " \"" + texto + "\"";
    system(comando.c_str());
}

// Funci�n para mostrar el historial del usuario
void mostrarHistorial(const string& nombreUsuario) {
    string rutaBase = "D:\\College Shit\\U shit\\Progra III\\Proyecto Final Final\\usuarios\\";
    string rutaArchivo = rutaBase + nombreUsuario + "\\Historial.txt";

    limpiarPantalla();
    cout << "=== HISTORIAL DE TRADUCCIONES ===" << endl;
    cout << "Usuario: " << nombreUsuario << endl;
    cout << "\n----------------------------------------\n" << endl;

    ifstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        string linea;
        bool hayContenido = false;

        while (getline(archivo, linea)) {
            cout << linea << endl;
            hayContenido = true;
        }

        if (!hayContenido) {
            cout << "El historial est� vac�o." << endl;
        }

        archivo.close();
    } else {
        cout << "Error: No se pudo abrir el archivo de historial." << endl;
    }

    cout << "\n----------------------------------------" << endl;
    pausar();
}

// Funci�n para registrar traducci�n en el historial
bool registrarTraduccion(const string& nombreUsuario, const string& palabraOrigen, const string& palabraDestino,
                        const string& idiomaOrigen, const string& idiomaDestino) {
    string rutaBase = "D:\\College Shit\\U shit\\Progra III\\Proyecto Final Final\\usuarios\\";
    string rutaArchivo = rutaBase + nombreUsuario + "\\Historial.txt";

    ofstream archivo(rutaArchivo, ios::app); // ios::app para a�adir al final del archivo
    if (archivo.is_open()) {
        archivo << "\nTraducci�n realizada:" << endl;
        archivo << "- Palabra original: " << palabraOrigen << " (" << idiomaOrigen << ")" << endl;
        archivo << "- Traducci�n: " << palabraDestino << " (" << idiomaDestino << ")" << endl;
        archivo << "- Fecha: " << __DATE__ << " " << __TIME__ << endl;
        archivo << "----------------------------------------" << endl;
        archivo.close();
        return true;
    } else {
        cout << "\nError al registrar la traducci�n en el historial." << endl;
        return false;
    }
}

// Funci�n para mostrar las palabras y seleccionar una
int seleccionarPalabra(const vector<string>& palabras) {
    int opcion;
    cout << "Lista de palabras:" << endl;
    for (int i = 0; i < palabras.size(); i++) {
        cout << i + 1 << ". " << palabras[i] << endl;
    }
    cout << "Seleccione el n�mero de la palabra a traducir: ";
    cin >> opcion;
    return opcion - 1; // Restamos 1 para que coincida con el �ndice del vector
}

void traduccionOffline(const string& nombreUsuario) {  // A�adimos el par�metro nombreUsuario
    limpiarPantalla();
    cout << "=== TRADUCCI�N OFFLINE ===" << endl;

    int idiomaOrigen = seleccionarIdioma("Seleccione el idioma de origen:");
    int idiomaDestino = seleccionarIdioma("Seleccione el idioma de destino:");

    if (idiomaOrigen == idiomaDestino) {
        cout << "Error: El idioma de origen y destino no pueden ser el mismo." << endl;
        pausar();
        return;
    }

    vector<string> palabrasOrigen = cargarPalabras(IDIOMAS[idiomaOrigen]);
    vector<string> palabrasDestino = cargarPalabras(IDIOMAS[idiomaDestino]);

    if (palabrasOrigen.empty() || palabrasDestino.empty()) {
        cout << "Error: No se pudieron cargar las palabras." << endl;
        pausar();
        return;
    }

    int indicePalabra = seleccionarPalabra(palabrasOrigen);

    if (indicePalabra >= 0 && indicePalabra < palabrasOrigen.size()) {
        cout << "Traducci�n:" << endl;
        cout << palabrasOrigen[indicePalabra] << " (" << IDIOMAS[idiomaOrigen] << ") -> ";
        cout << palabrasDestino[indicePalabra] << " (" << IDIOMAS[idiomaDestino] << ")" << endl;

        // Registrar la traducci�n en el historial
        if (registrarTraduccion(nombreUsuario,
                              palabrasOrigen[indicePalabra],
                              palabrasDestino[indicePalabra],
                              IDIOMAS[idiomaOrigen],
                              IDIOMAS[idiomaDestino])) {
            cout << "\nTraducci�n registrada en el historial." << endl;
        }

        // Reproducir audio de la palabra original
        cout << "\nReproduciendo palabra en " << IDIOMAS[idiomaOrigen] << ":" << endl;
        reproducirAudio(palabrasOrigen[indicePalabra], IDIOMAS[idiomaOrigen]);

        pausar();

        // Reproducir audio de la traducci�n
        cout << "\nReproduciendo traducci�n en " << IDIOMAS[idiomaDestino] << ":" << endl;
        reproducirAudio(palabrasDestino[indicePalabra], IDIOMAS[idiomaDestino]);
    } else {
        cout << "Error: Selecci�n de palabra inv�lida." << endl;
    }

    pausar();
}

// Funci�n simple de hash
uint32_t simpleHash(const string& str) {
    uint32_t hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

void limpiarPantalla() {
    system("cls");
}

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

bool directorioExiste(const string& ruta) {
    DWORD atributos = GetFileAttributesA(ruta.c_str());
    return (atributos != INVALID_FILE_ATTRIBUTES &&
            (atributos & FILE_ATTRIBUTE_DIRECTORY));
}

bool usuarioExiste(const string& nombreUsuario) {
    string rutaBase = "D:\\College Shit\\U shit\\Progra III\\Proyecto Final Final\\usuarios\\";
    string rutaUsuario = rutaBase + nombreUsuario;
    return directorioExiste(rutaUsuario);
}

bool verificarContrasena(const string& nombreUsuario, const string& contrasena) {
    string rutaBase = "D:\\College Shit\\U shit\\Progra III\\Proyecto Final Final\\usuarios\\";
    string rutaArchivo = rutaBase + nombreUsuario + "\\password.txt";

    ifstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        uint32_t hashAlmacenado;
        archivo >> hashAlmacenado;
        archivo.close();

        uint32_t hashIngresado = simpleHash(contrasena);
        return hashAlmacenado == hashIngresado;
    }
    return false;
}

void iniciarSesion() {
    string nombreUsuario, contrasena;

    limpiarPantalla();
    cout << "=== INICIAR SESI�N ===" << endl;
    cout << "Ingrese su nombre de usuario: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nombreUsuario);

    if (!usuarioExiste(nombreUsuario)) {
        cout << "Error: El usuario no existe." << endl;
        pausar();
        return;
    }

    cout << "Ingrese su contrase�a: ";
    getline(cin, contrasena);

    if (verificarContrasena(nombreUsuario, contrasena)) {
        cout << "Inicio de sesi�n exitoso. �Bienvenido, " << nombreUsuario << "!" << endl;
        pausar();

        int opcionUsuario;
        do {
            opcionUsuario = mostrarMenuUsuario();

            switch (opcionUsuario) {
                case 1:
                    cout << "Has seleccionado: Traducci�n Offline" << endl;
                    traduccionOffline(nombreUsuario);
                    break;
                case 2:
                    cout << "Has seleccionado: Historial" << endl;
                    mostrarHistorial(nombreUsuario);
                    break;
                case 3:
                    cout << "Cerrando sesi�n..." << endl;
                    break;
            }

            if (opcionUsuario != 4) {
                pausar();
            }
        } while (opcionUsuario != 4);

    } else {
        cout << "Error: Contrase�a incorrecta." << endl;
    }
    pausar();
}

bool crearCarpetaUsuario(const string& nombreUsuario) {
    string rutaBase = "D:\\College Shit\\U shit\\Progra III\\Proyecto Final Final\\usuarios\\";
    string rutaCompleta = rutaBase + nombreUsuario;

    if (directorioExiste(rutaCompleta)) {
        cout << "\nError: El usuario '" << nombreUsuario << "' ya existe." << endl;
        return false;
    }

    int resultado = _mkdir(rutaCompleta.c_str());
    if (resultado == 0) {
        cout << "\nUsuario '" << nombreUsuario << "' creado exitosamente." << endl;
        return true;
    } else {
        cout << "\nError al crear la carpeta del usuario." << endl;
        return false;
    }
}

string solicitarNombreUsuario() {
    string nombreUsuario;
    cout << "\n=== CREAR USUARIO ===" << endl;
    cout << "Ingrese el nombre de usuario deseado: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nombreUsuario);
    return nombreUsuario;
}

string solicitarContrasena() {
    string contrasena;
    cout << "Ingrese la contrase�a: ";
    getline(cin, contrasena);
    return contrasena;
}

// Nueva funci�n para crear el archivo de historial
bool crearHistorial(const string& nombreUsuario) {
    string rutaBase = "D:\\College Shit\\U shit\\Progra III\\Proyecto Final Final\\usuarios\\";
    string rutaArchivo = rutaBase + nombreUsuario + "\\Historial.txt";

    ofstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        archivo << "=== HISTORIAL DE ACTIVIDADES ===" << endl;
        archivo << "Usuario creado: " << nombreUsuario << endl;
        archivo.close();
        cout << "\nArchivo de historial creado exitosamente." << endl;
        return true;
    } else {
        cout << "\nError al crear el archivo de historial." << endl;
        return false;
    }
}

// Funci�n modificada de guardarContrasena
bool guardarContrasena(const string& nombreUsuario, const string& contrasena) {
    string rutaBase = "D:\\College Shit\\U shit\\Progra III\\Proyecto Final Final\\usuarios\\";
    string rutaArchivo = rutaBase + nombreUsuario + "\\password.txt";

    ofstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        uint32_t hashContrasena = simpleHash(contrasena);
        archivo << hashContrasena;
        archivo.close();
        cout << "\nContrase�a guardada exitosamente." << endl;

        // Crear el archivo de historial despu�s de guardar la contrase�a
        return crearHistorial(nombreUsuario);
    } else {
        cout << "\nError al guardar la contrase�a." << endl;
        return false;
    }
}

void crearUsuario() {
    bool usuarioCreado = false;

    while (!usuarioCreado) {
        limpiarPantalla();
        string nombreUsuario = solicitarNombreUsuario();

        if (nombreUsuario.empty()) {
            cout << "\nError: El nombre de usuario no puede estar vac�o." << endl;
            pausar();
            continue;
        }

        bool caracteresInvalidos = false;
        string caracteresNoPermitidos = "\\/:*?\"<>|";
        for (char c : nombreUsuario) {
            if (caracteresNoPermitidos.find(c) != string::npos) {
                caracteresInvalidos = true;
                break;
            }
        }

        if (caracteresInvalidos) {
            cout << "\nError: El nombre de usuario contiene caracteres no permitidos." << endl;
            cout << "No se permiten los siguientes caracteres: \\ / : * ? \" < > |" << endl;
            pausar();
            continue;
        }

        usuarioCreado = crearCarpetaUsuario(nombreUsuario);

        if (usuarioCreado) {
            string contrasena = solicitarContrasena();
            if (!guardarContrasena(nombreUsuario, contrasena)) {
                cout << "\nAdvertencia: Hubo problemas al crear algunos archivos del usuario." << endl;
                cout << "Se recomienda eliminar la carpeta y crear el usuario nuevamente." << endl;
            } else {
                cout << "\nUsuario creado exitosamente con todos sus archivos." << endl;
            }
        }

        pausar();
    }
}

int mostrarMenu() {
    int opcion;

    while (true) {
        limpiarPantalla();
        cout << "=== MENU PRINCIPAL ===" << endl;
        cout << "1. Crear usuario" << endl;
        cout << "2. Iniciar sesi�n" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese su opci�n: ";

        if (cin >> opcion) {
            if (opcion >= 1 && opcion <= 3) {
                return opcion;
            }
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opci�n inv�lida. Por favor, intente de nuevo." << endl;
        pausar();
    }
}

int mostrarMenuUsuario() {
    int opcion;

    while (true) {
        limpiarPantalla();
        cout << "=== MEN� DE USUARIO ===" << endl;
        cout << "1. Traducci�n Offline" << endl;
        cout << "2. Historial" << endl;
        cout << "3. Cerrar Sesi�n" << endl;
        cout << "Ingrese su opci�n: ";

        if (cin >> opcion) {
            if (opcion >= 1 && opcion <= 4) {
                return opcion;
            }
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opci�n inv�lida. Por favor, intente de nuevo." << endl;
        pausar();
    }
}

int main() {
    int opcion;

    do {
        opcion = mostrarMenu();

        switch (opcion) {
            case 1:
                crearUsuario();
                break;
            case 2:
                iniciarSesion();
                break;
            case 3:
                cout << "Gracias por usar el programa. �Hasta luego!" << endl;
                break;
        }

        if (opcion != 3) {
            pausar();
        }
    } while (opcion != 3);

    return 0;
}
