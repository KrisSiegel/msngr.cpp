#include <iostream>
#include "msngr.hpp"

using namespace std;
using namespace msg;

int main() {
    Msngr msngr;

    msngr.On("Topic", [](Message message) {
        cout << "On Callback with topic " << message.Topic() << endl;
    });

    msngr.Emit("Topic");

    msngr.Drop("Topic");

    msngr.Emit("Topic");
}