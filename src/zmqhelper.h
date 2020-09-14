#include <zmq.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <exception>

// Helper class for common functions
class ZmqReqRep {
public:
    bool send_data(const std::string & datum, int flags = 0) {
        zmq::message_t request(datum.size());
        memcpy(request.data(), datum.data(), datum.size());

        bool sent = _socket.send(request, flags);
        return (sent);
    }

    // Return ZMQ message as a string
    std::string receive_data() {
        zmq::message_t reply;
        _socket.recv(&reply);

        return std::string(static_cast<char*>(reply.data()), reply.size());
    }

    ZmqReqRep(){};

protected:
    zmq::context_t _ctx;
    zmq::socket_t _socket;
    std::string _connection;

    ZmqReqRep(int sock_type): _ctx(1), _socket(_ctx, sock_type) {}
};

class ZmqClient: virtual public ZmqReqRep {
public:
    ZmqClient(): ZmqReqRep(ZMQ_REQ) {
        try_connect();
    }

    bool try_connect() {
        int port = 5555;
        std::string ip = "127.0.0.1";

        std::stringstream ss;
        ss << "tcp://" << ip << ":" << port;
        _connection = ss.str();

        std::cout << "Trying to connect to \"" << _connection << "\"" << std::endl;
        try {
            _socket.connect(_connection);
        } catch (...){
            std::cout << "Cannot connect!" << std::endl;
            return false;
        }

        std::cout << "Successfully connected!" << std::endl;
        return true;
    }
};

class ZmqServer: virtual public ZmqReqRep {
public:
    ZmqServer(): ZmqReqRep(ZMQ_REP) {
        try_bind();
    }

    bool try_bind() {
        int port = 5555;

        std::stringstream ss;
        ss << "tcp://*:" << port;
        _connection = ss.str();

        std::cout << "Trying to connect to \"" << _connection << "\"" << std::endl;
        try {
            _socket.bind(_connection);
        } catch (...){
            std::cout << "Cannot connect!" << std::endl;
            return false;
        }

        std::cout << "Successfully connected!" << std::endl;
        return true;
    }
};