#include "ClientProxy.h"

#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <unistd.h>

/* Representa una conexion con uno de los clientes(sensores) del rio */
ClientProxy::ClientProxy(Socket *conexion)
	: conexion(conexion),
	  finalizado(false),
	  buffer(""){
}

ClientProxy::~ClientProxy() {
}


void ClientProxy::say_hello(){
	char caa[10];
	conexion->recibir(caa, 1);
	caa[1] = '\0';
	std::cout << "ME ENVIARON ESTO: " << caa << "\n";

	char message = 1;
	conexion->enviar(&message, 1);
	std::cout << "ENVIADO EL HEADER\n";
	char c = 65;
	conexion->enviar(&c, 1);
	std::cout << "EL TRUE\n";
	conexion->recibir(caa, 1);
	std::cout << "me mandaron: " << caa[0] << std::endl;
}

/* Se ejecuta en un hilo separado al del Socket que acepta conexiones,
 * por eso tiene su propio Socket peer y el mapa que hay que actualizar.
 * */
void ClientProxy::run(){
	say_hello();
	bool seguir = true;
	std::cout << "ALGUIEN SE CONECTO\n";
	while (seguir && !finalizado){
		std::cout << "ENTRO AL LOOP\n";
		char option;
		seguir = conexion->recibir(&option, 1);
		if (seguir){
			std::cout << "LEYO ALGO\n";
			if (option == 'i') {
				std::cout << "IZQ\n";
			} else if (option == 'd') {
				std::cout << "DER\n";
			}
		}
	}
	conexion->cerrar();
	delete conexion;
	std::cout << "FIN\n";
}

/* El socket aceptor envia una senial de terminacion porque se quiere finalizar
 * el servidor, eso implica cerrar todas las conexiones con los clientes.
 * Se marca como finalizado y se cierra la conexion con la otra punta
 * */
bool ClientProxy::finalizar(){
	this->finalizado = true;
	bool fin = conexion->cerrar();
	return fin;
}
