#include <iostream>
#include "msngr.hpp"

using namespace std;
using namespace msg;

int main() {
    Msngr msngr;

    msngr.On("Topic", []() {
        cout << "On Callback" << endl;
    });

    msngr.Emit("Topic");

    msngr.Drop("Topic");
}