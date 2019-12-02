#pragma once

#include <string>

// Abstract Factory creates factories, which produce related products.
// This design structure is preferred to normal Factory.
// The switch case statement is not good practice.

// First Define a product
struct Product {
  // product propteries
  virtual std::string name() { return _name; };

 protected:
  std::string _name{"Product Default"};
};

class ProductA : public Product {
 public:
  ProductA() { _name = "Product A"; }
  // std::string name() override { return _name; };
};

class ProductB : public Product {
 public:
  ProductB() { _name = "Product B"; }
  // std::string name() override { return _name; };
};

// Creational

class AbstractFactory {
 public:
  virtual Product getProduct() { return Product(); };
};

// Factory creates products depending on a product type request
class ProductAFactory : public AbstractFactory {
 public:
  Product getProduct() override { return ProductA(); }
};

class ProductBFactory : public AbstractFactory {
 public:
  Product getProduct() override { return ProductB(); }
};

class ProductDefaultFactory : public AbstractFactory {
 public:
  Product getProduct() override { return Product(); }
};

class FactoryMaker {
 public:
  enum class Type { A, B };
  static AbstractFactory create(Type type) {
    if (type == Type::A) return ProductAFactory();
    if (type == Type::B) return ProductBFactory();
  }
  // creates factory making default product
  static AbstractFactory create() { return ProductDefaultFactory(); }
};
