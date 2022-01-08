// imagenes_panoramicass.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "utils/reconstruction_manager.h"


void set_commands(std::vector<std::string> command_inputs) {
	std::vector<std::string>::iterator it = command_inputs.begin();
	while (it != command_inputs.end()) {
		int a = 1;
	}
}

int main(int argc, char** argv)
{
	
	//Read the image file 
	std::string current_exec_name = argv[0]; // Name of the current exec program
	std::vector<std::string> all_args;
    reconstruction_manager manager;
	if (argc > 1) {
		all_args.assign(argv + 1, argv + argc);
		manager.add_parameters(&all_args);
	}

	manager.reconstruct_scene();
    return 0;
}




// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
