#include <iostream>
#include "msngr.hpp"

int main() {
    Msngr msngr;

    msngr.on("topic1", []() {
        std::cout << "topic1 subscriber" << std::endl;
    });

    msngr.emit("topic1");
    msngr.emit("topic5", "cat2");
    msngr.emit("topic3");
    msngr.emit("topic3");
    msngr.emit("topic1", "cat7");
}