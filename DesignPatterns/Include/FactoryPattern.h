#pragma once

#include <string>

// A Factory creates a different type of products using the same interface

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
// Factory creates products depending on a product type request
class ProductFactory {
 public:
  enum class ProductType { A, B, C, D };

  static Product getProduct(ProductType product) {
    switch (product) {
      case ProductType::A:
        return ProductA();
        break;
      case ProductType::B:
        return ProductB();
        break;
      default:  // others create default product
        return Product();
        break;
    }
  }
};
