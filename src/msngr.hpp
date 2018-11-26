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

using std::string;
using std::function;
using std::vector;

class Msngr {
    public:
        struct Message {
            public:
                Message() {};
                Message(optional<string> topic, optional<string> category, optional<string> subcategory) : topicOpt(topic), categoryOpt(category), subcategoryOpt(subcategory) {};

                optional<string> topicOpt = nullopt;
                optional<string> categoryOpt = nullopt;
                optional<string> subcategoryOpt = nullopt;
        };

        Msngr() {};
        ~Msngr() {};

        void emit(string topic) {
            Message msg(topic, nullopt, nullopt);
            internal_emit(msg);
        };

        void emit(string topic, string category) {
            Message msg(topic, category, nullopt);
            internal_emit(msg);
        };

        void emit(string topic, string category, string subcategory) {
            Message msg(topic, category, subcategory);
            internal_emit(msg);
        };

        void emit(Message message) {
            internal_emit(message);
        };
        
        void on(string topic, const function<void()> &fn) {
            Message msg(topic, nullopt, nullopt);
            internal_on(msg, fn);
        }

        void on(string topic, string category, const function<void()> &fn) {
            Message msg(topic, category, nullopt);
            internal_on(msg, fn);
        }

        void on(string topic, string category, string subcategory, const function<void()> &fn) {
            Message msg(topic, category, subcategory);
            internal_on(msg, fn);
        }

        void on(Message message, const function<void()> &fn) {
            internal_on(message, fn);
        }

    private:
        class Subscription {
            public:
                Message message;
                const function<void()> &func;

                Subscription(Message msg, const function<void()> &fn) : message(msg), func(fn) {};
        };
        vector<Subscription> subscriptions;

        void internal_emit(Message message);
        bool internal_on(Message message, const function<void()> &fn);

        void internal_subscribe(Message message);
        void internal_unsubscribe(Message message);
};

void Msngr::internal_emit(Message message) {
    for (Subscription sub : subscriptions) {
        if (message.topicOpt && message.topicOpt.value() == sub.message.topicOpt.value()) {
            sub.func();
        }
    }
};

bool Msngr::internal_on(Message message, const function<void()> &fn) {
    Subscription sub(message, fn);
    subscriptions.push_back(sub);
    return true;
};

#endif