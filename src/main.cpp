#include "zmqhelper.h"
#include "addressbook.pb.h"
#include <string>
#include <iostream>

int main () {
    // Fill person data
    tutorial::Person person;
    person.set_name("Gio");

    // Prepare our context and socket
    std::cout << "Starting ZmqClient test..." << std::endl;
    ZmqClient testClient;
    
    for (int request_nbr = 0; request_nbr < 10; request_nbr++) {
        // Changing ID just to make sure it works
        person.set_id(request_nbr);
        std::cout << "Sending ID " << request_nbr << "…" << std::endl;

        // ZMQ sends strings, must serialize first
        std::string msg_str;
        person.SerializeToString(&msg_str);
        testClient.send_data(msg_str);
        std::cout << "Message Sent..." << std::endl;

        // Blocks until ping is received
        testClient.receive_data();
        std::cout << "Received Ping " << request_nbr << std::endl;
    }

    std::cout << "Finished job!" << std::endl;
    return 0;
}
