#include <algorithm>
#include <cstring>
#include <iterator>
#include <netdb.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <vector>
#include "Socket.h"
#include "ClientProxy.h"
#include "Constants.h"

#include <iostream>

ClientProxy::ClientProxy(Socket* peerskt)
    : peerskt(peerskt), keep_connection(true) {
}

ClientProxy::~ClientProxy() {
    delete peerskt;
}

void ClientProxy::OpenConnection() {
    // Empty placeholder method
}

void ClientProxy::CloseConnection() {
	keep_connection = false;
    peerskt->Close();
}

bool ClientProxy::HandleLine(std::string const& line) {
    if (line.find("hola") != std::string::npos){
        return false;
    }
    return true;
    /*std::vector<std::string> command_and_args;
    std::istringstream is(line);

    std::copy(std::istream_iterator<std::string>(is),
              std::istream_iterator<std::string>(),
              std::back_inserter(command_and_args));

    std::string const& command = command_and_args[0];
    if (command == "fin") {
        return false;
    } else if (command == "consultar") {
        SocketSectionSender sender(*peerskt);
        peerskt->Send("respuesta\n");
        if (command_and_args.size() > 1) {
            data.ApplyTo(command_and_args[2], sender);
        } else {
            data.ApplyToAll(sender);
        }
        peerskt->Send("fin\n");
        return false;
    } else if (command == "conector") {
        section = &data.GetSection(command_and_args[2]);
        return true;
    } else if (command == "actualizar") {
        section->Update(command_and_args[2], command_and_args[4]);
        return true;
    } else {
        return false;
    }*/
}

void ClientProxy::say_hello(){
	char caa[10];
	peerskt->Read(caa, 1);
	caa[1] = '\0';
	std::cout << "ME ENVIARON ESTO: " << caa << "\n";

	char message = 1;
	peerskt->Send(&message, 1);
	std::cout << "ENVIADO EL HEADER\n";
	char c = 65;
	peerskt->Send(&c, 1);
	std::cout << "EL TRUE\n";
	peerskt->Read(caa, 1);
	std::cout << "me mandaron: " << caa[0] << std::endl;
}

void ClientProxy::ThreadMain() {
	std::cout << "ALGUIEN SE CONECTO\n";
    std::stringstream ss;
    // size_t current_line = 0;
    say_hello();
    bool cont = true;
    while (keep_connection && cont) {
    	std::cout << "ENTRO AL LOOP\n";
        char option;
        cont = peerskt->Read(&option, 1);
        if (cont){
			std::cout << "LEYO ALGO\n";
			if (option == 'i') {
				std::cout << "IZQ\n";
			} else if (option == 'd') {
				std::cout << "DER\n";
			}
        }
    }
    std::cout << "FIN\n";
}
