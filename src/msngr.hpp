#ifndef MSNGR_HPP
#define MSNGR_HPP

#pragma once
#if __has_include(<optional>)
#   include <optional>
    using std::optional;
    using std::nullopt;
#elif __has_include(<experimental/optional>)
#   include <experimental/optional>
    using std::experimental::optional;
    using std::experimental::nullopt;
#else
#   error Please use a newer compiler; msngr requires C++14 with experimental features or higher.
#endif

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::string;
using std::function;
using std::vector;
using std::unordered_map;
using std::transform;

/*
    Msngr

*/
class Msngr {
    public:
        struct Message;

        Msngr() {};
        ~Msngr() {};

        void emit(string topic);
        void emit(string topic, string category);
        void emit(string topic, string category, string subcategory);

        void on(string topic, const function<void()> &fn);
        void on(string topic, string category, const function<void()> &fn);
        void on(string topic, string category, string subcategory, const function<void()> &fn);

        void drop(string topic);
        void drop(string topic, string category);
        void drop(string topic, string category, string subcategory);

    private:
        class Subscription;
        unsigned int _index = 0;
        vector<Subscription> _subscriptions_index;
        unordered_map<string, vector<unsigned>> _subscriptions_topic;
        unordered_map<string, vector<unsigned int>> _subscriptions_topic_subcategory;
        unordered_map<string, vector<unsigned int>> _subscriptions_topic_category_subcategory;

        // Internal Utilities
        Message internal_normalize(Message message);

        // Internal APIs
        void internal_emit(Message message);
        bool internal_on(Message message, const function<void()> &fn);
        bool internal_drop(Message message);

        void internal_subscribe(Message message);
        void internal_unsubscribe(Message message);
};

// Nested class definitions
// Public
struct Msngr::Message {
    public:
        Message() {};
        Message(optional<string> topic, optional<string> category, optional<string> subcategory) : topicOpt(topic), categoryOpt(category), subcategoryOpt(subcategory) {};

        optional<string> topicOpt = nullopt;
        optional<string> categoryOpt = nullopt;
        optional<string> subcategoryOpt = nullopt;
};

// Private
class Msngr::Subscription {
    public:
        Message message;
        const function<void()> &func;

        Subscription(Message msg, const function<void()> &fn) : message(msg), func(fn) {};
};

// Msngr::* definitions
// Public
void Msngr::emit(string topic) {
    Message msg(topic, nullopt, nullopt);
    internal_emit(msg);
};

void Msngr::emit(string topic, string category) {
    Message msg(topic, category, nullopt);
    internal_emit(msg);
};

void Msngr::emit(string topic, string category, string subcategory) {
    Message msg(topic, category, subcategory);
    internal_emit(msg);
};

void Msngr::on(string topic, const function<void()> &fn) {
    Message msg(topic, nullopt, nullopt);
    internal_on(msg, fn);
};

void Msngr::on(string topic, string category, const function<void()> &fn) {
    Message msg(topic, category, nullopt);
    internal_on(msg, fn);
};

void Msngr::on(string topic, string category, string subcategory, const function<void()> &fn) {
    Message msg(topic, category, subcategory);
    internal_on(msg, fn);
};

void Msngr::drop(string topic) {

};

void Msngr::drop(string topic, string category) {

};

void Msngr::drop(string topic, string category, string subcategory) {

};

// Private Utilities
Msngr::Message Msngr::internal_normalize(Message message) {
    Message normalized;
    if (message.topicOpt != nullopt) {
        string val = message.topicOpt.value();
        transform(val.begin(), val.end(), val.begin(), ::tolower);
        normalized.topicOpt = optional<string>(val);
    }

    if (message.categoryOpt != nullopt) {
        string val = message.categoryOpt.value();
        transform(val.begin(), val.end(), val.begin(), ::tolower);
        normalized.categoryOpt = optional<string>(val);
    }

    if (message.subcategoryOpt != nullopt) {
        string val = message.subcategoryOpt.value();
        transform(val.begin(), val.end(), val.begin(), ::tolower);
        normalized.subcategoryOpt = optional<string>(val);
    }

    return normalized;
};

// Private APIs
void Msngr::internal_emit(Message message) {
    message = internal_normalize(message);
    /*for (Subscription sub : subscriptions) {
        if (message.topicOpt && message.topicOpt.value() == sub.message.topicOpt.value()) {
            sub.func();
        }
    }*/
};

bool Msngr::internal_on(Message message, const function<void()> &fn) {
    Subscription sub(message, fn);

    
    return true;
};

bool Msngr::internal_drop(Message message) {

};

#endif