#include <iostream>
#include "msngr.hpp"

using namespace std;

int main() {
    // Create the instance of msngr that will be used throughout
    Msngr msngr;

    // Now, how do we emit simple messages?
    msngr.emit("MyTopic");

    // Simple, right? But, you had no listeners for that particular topic so it never went anywhere
    // So, let's setup one now!
    msngr.on("MyTopic", []() {
        cout << "The MyTopic listener was executed" << endl;
    });

    // Great! A listener! Now let's emit again
    msngr.emit("MyTopic");

    // You should have gotten the console output "The MyTopic listener was executed"
    // Woohoo!
    // Don't forget to clean up the handler when you're done with it
    msngr.drop("MyTopic");
    
    // But wait, there's more!
    // What if you wanted to capture
}