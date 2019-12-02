#include "pch.h"

#include "FactoryPattern.h"

TEST(TestFactoryPattern, GetProduct) {
  // We have different internal logic, but user does not care.
  // The consumer only specifies the type of the product

  // usage with static method. ProductFactory::getProduct
  Product productA = ProductFactory::getProduct(ProductFactory::ProductType::A);
  Product productB = ProductFactory::getProduct(ProductFactory::ProductType::B);
  EXPECT_EQ(productA.name(), "Product A");
  EXPECT_EQ(productB.name(), "Product B");

  // factory creates default product if product type is C and D.
  ProductFactory factory;  // usage with object notation.
  Product productC = factory.getProduct(ProductFactory::ProductType::C);
  Product productD = factory.getProduct(ProductFactory::ProductType::D);
  EXPECT_EQ(productC.name(), "Product Default");
  EXPECT_EQ(productD.name(), "Product Default");
}
