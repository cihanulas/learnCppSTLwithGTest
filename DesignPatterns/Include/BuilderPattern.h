#pragma once

// builds a complex object using simple objects step by step
#include <memory>
#include <string>  // for just helpers
#include <vector>

/*
https://www.tutorialspoint.com/design_pattern/builder_pattern.htm

We have considered a business case of fast-food restaurant where a typical meal
could be a burger and a cold drink. Burger could be either a Veg Burger or
Chicken Burger and will be packed by a wrapper. Cold drink could be either a
coke or pepsi and will be packed in a bottle.

We are going to create an Item interface representing food items such as burgers
and cold drinks and concrete classes implementing the Item interface and a
Packing interface representing packaging of food items and concrete classes
implementing the Packing interface as burger would be packed in wrapper and cold
drink would be packed as bottle.

We then create a Meal class having ArrayList of Item and a MealBuilder to build
different types of Meal objects by combining Item. BuilderPatternDemo, our demo
class will use MealBuilder to build a Meal.

*/

// First Create Packing interface and their concrete classes
class Packing {
  virtual std::string pack() { return "Default Pack"; };
};

class Wrapper : public Packing {
 public:
  std::string pack() override { return "Wrapper"; };
};

class Bottle : public Packing {
 public:
  std::string pack() override { return "Bottle"; }
};

// Item: Food items will be created based on this
class Item {
 public:
  virtual std::string name() { return "Default item"; };
  virtual Packing packing() { return Packing(); };
  virtual double price() { return 0; };
};

class Burger : public Item {
 public:
  Packing packing() override { return Wrapper(); }
};

class ColdDrink : public Item {
 public:
  Packing packing() override { return Bottle(); }
};

class VegBurger : public Burger {
 public:
  double price() override { return 10; }
  std::string name() override { return "Veg Burger"; }
};

class ChickenBurger : public Burger {
 public:
  double price() override { return 20; }
  std::string name() { return "Chicken Burger"; }
};

class Coke : public ColdDrink {
 public:
  double price() override { return 3; }
  std::string name() override { return "Coke"; }
};

class Pepsi : public ColdDrink {
 public:
  double price() override { return 3; }
  std::string name() override { return "Pepsi"; }
};

class Meal {
  std::vector<std::unique_ptr<Item>> _items;

 public:
  void addItem(std::unique_ptr<Item> it) { _items.emplace_back(std::move(it)); }

  double getCost() {
    double cost = 0;
    for (auto& item : _items) {
      cost += item->price();
    }
    return cost;
  }
  std::vector<std::string> item_names_in_the_meal() {
    std::vector<std::string> items;
    for (auto& it : _items) {
      items.push_back(it->name());
    }
    return items;
  };
};

class MealBuilder {
 public:
  Meal VegMeal() {
    Meal meal = Meal();
    meal.addItem(std::make_unique<VegBurger>());
    meal.addItem(std::make_unique<Coke>());
    return meal;
  }

  Meal NonVegMeal() {
    Meal meal = Meal();
    meal.addItem(std::make_unique<ChickenBurger>());
    meal.addItem(std::make_unique<Pepsi>());
    return meal;
  }
};
