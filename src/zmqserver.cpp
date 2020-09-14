#include "zmqhelper.h"
#include "addressbook.pb.h"
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#include <google/protobuf/text_format.h>

#define sleep(n)    Sleep(n)
#endif

int main ()
{
    std::cout << "Starting ZmqServer test..." << std::endl;
    ZmqServer testServer;

    while (true) {
        // Blocks until message is received from client
        std::string msg_str = testServer.receive_data();
        std::cout << "Received message!" << std::endl;

        tutorial::Person person;
        person.ParseFromString(msg_str);

        std::cout << "ID: " << person.id() << std::endl;
        std::cout << "Name: " << person.name() << std::endl;

        // Do some 'work' lol
        sleep(3);

        // Send reply back to client
        testServer.send_data("Ping");
    }
    return 0;
}