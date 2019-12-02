#pragma once
#include "pch.h"

#include "AbstractFactory.h"

TEST(TestFactoryPattern, GetProduct) {
  // First Create Factories
  auto fA = FactoryMaker::create(FactoryMaker::Type::A);
  auto fB = FactoryMaker::create(FactoryMaker::Type::B);
  auto fDefault = FactoryMaker::create();

  Product productA = fA.getProduct();
  Product productB = fB.getProduct();
  Product productDefault = fDefault.getProduct();
  EXPECT_EQ(productA.name(), "Product A");
  EXPECT_EQ(productB.name(), "Product B");
  EXPECT_EQ(productDefault.name(), "Product Default");
}
