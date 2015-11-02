#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

#include "Servidor.h"

#define ARGUMENTOS_SERVIDOR 2

int main(int argc, char *argv[]) {
	std::string puerto = "socks";
	if (argc == ARGUMENTOS_SERVIDOR){
		puerto = std::string(argv[1]);
	}

	Servidor servidor(puerto);
	servidor.iniciar();
	return 0;
}
