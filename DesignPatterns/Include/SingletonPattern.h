#pragma once

#include <memory>

class Singleton {
  Singleton(){};
  static Singleton* instance;

 public:
  // not thread safe
  static Singleton& getInstance() {
    if (!instance) {
      instance = new Singleton();
    }
    return *instance;
  };
};

Singleton* Singleton::instance = nullptr;

class SingletonThreadSafe {
  SingletonThreadSafe() {}

 public:
  static SingletonThreadSafe& getInstance() {
    static SingletonThreadSafe instance;  // Guaranteed to be destroyed.
                                          // Instantiated on first use.
    return instance;
  }

 public:
  SingletonThreadSafe(SingletonThreadSafe const&) = delete;
  void operator=(SingletonThreadSafe const&) = delete;
};

// A Concrete example
#include <iostream>
#include <string>

class Logger : SingletonThreadSafe {
 public:
  std::string log(std::string str) {
    std::cout << str << std::endl;
    return str;
  };

  static Logger& getLogger() { return *static_cast<Logger*>(&getInstance()); }
};
