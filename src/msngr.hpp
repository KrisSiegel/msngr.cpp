/*
    msngr.cpp

    A pubsub, in-process message bus to allow decoupling of concerns within a single application
    and its utilized libraries.
*/
#ifndef MSG_MSNGR_HPP
#define MSG_MSNGR_HPP

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
#include <locale>
#include <unordered_map>

using std::string;
using std::function;
using std::vector;
using std::transform;
using std::find_if;
using std::isspace;
using std::unordered_map;

// The msg namespace contains all used, public classes and structs within msngr.cpp
namespace msg {

    // Message is mostly a simple data structure with a topic, category and subcategory. It handles basic getter and setter local as well
    // as providing a normalized copied of what the developer created (this is for better indexing without losing fidelity).
    struct Message {
        public:
            Message() {};
            Message(string topic) : mTopic(topic) {};
            Message(string topic, string category) : mTopic(topic), mCategory(category) {};
            Message(string topic, string category, string subcategory) : mTopic(topic), mCategory(category), mSubcategory(subcategory) {};
            
            ~Message() {};

            string Topic() { return mTopic; };
            void Topic(string topic) { mTopic = topic; };

            string Category() { return mCategory; }
            void Category(string category) { mCategory = category; };

            string Subcategory() { return mSubcategory; }
            void Subcategory(string subcategory) { mSubcategory = subcategory; };

            Message NormalizedCopy();

        private:
            string mTopic;
            string mCategory;
            string mSubcategory;

            static void tolowercase(string& str);
            static void trim(string& str);
    };

    void Message::tolowercase(string &str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    };

    void Message::trim(string& str) {
        // left trim
        str.erase(str.begin(), find_if(str.begin(), str.end(), [](int ch) {
            return !isspace(ch);
        }));

        // right trim
        str.erase(find_if(str.rbegin(), str.rend(), [](int ch) {
            return !isspace(ch);
        }).base(), str.end());
    };

    Message Message::NormalizedCopy() {
        string t = mTopic;
        trim(t);
        tolowercase(t);

        string c = mCategory;
        trim(c);
        tolowercase(c);

        string s = mSubcategory;
        trim(s);
        tolowercase(s);

        Message result;
        result.Topic(t);
        result.Category(c);
        result.Subcategory(s);

        return result;
    };

    struct Subscription {
        public:
            Subscription(Message message, const function<void()> &fn) : mMessage(message.NormalizedCopy()), mFunc(fn) {};

        private:
            const Message mMessage;
            const function<void()> &mFunc;
    };

    class Msngr {
        public:
            Msngr() {};
            ~Msngr() {};

            void Emit(Message message) { emit(message); };
            void Emit(string topic) { emit(Message(topic)); };
            void Emit(string topic, string category)  { emit(Message(topic, category)); };
            void Emit(string topic, string category, string subcategory)  { emit(Message(topic, category, subcategory)); };

            void On(Subscription subscription) { on(subscription); };
            void On(Message message, const function<void()> &fn) { on(Subscription(message, fn)); };
            void On(string topic, const function<void()> &fn) { on(Subscription(Message(topic), fn)); };
            void On(string topic, string category, const function<void()> &fn) { on(Subscription(Message(topic, category), fn)); };
            void On(string topic, string category, string subcategory, const function<void()> &fn)  { on(Subscription(Message(topic, category, subcategory), fn)); };

            void Drop(string topic) { drop(Message(topic)); };
            void Drop(string topic, string category)  { drop(Message(topic, category)); };
            void Drop(string topic, string category, string subcategory)  { drop(Message(topic, category, subcategory)); };

        private:


            bool emit(Message message);
            bool on(Subscription subscription);
            bool drop(Message message);
    };

    bool Msngr::emit(Message message) {
        std::cout << "Msngr::emit" << std::endl;
    };

    bool Msngr::on(Subscription subscription) {
        std::cout << "Msngr::on" << std::endl;
    };

    bool Msngr::drop(Message message) {
        std::cout << "Msngr::drop" << std::endl;
    };
};

#endif