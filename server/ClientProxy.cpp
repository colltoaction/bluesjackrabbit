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

ClientProxy::ClientProxy(Socket* peerskt)
    : peerskt(peerskt) {
}

ClientProxy::~ClientProxy() {
    delete peerskt;
}

void ClientProxy::OpenConnection() {
    // Empty placeholder method
}

void ClientProxy::CloseConnection() {
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

void ClientProxy::ThreadMain() {
    std::stringstream ss;
    size_t current_line = 0;
    while (peerskt->Read(ss) > 0) {
        std::string line;
        while (!std::getline(ss, line).eof()) {
            if (!HandleLine(line)) {
                peerskt->Close(); // reached end of message
                return;
            }

            // current_line = ss.tellg();
        }

        ss.seekg(current_line);
        ss.clear();
    }
}
