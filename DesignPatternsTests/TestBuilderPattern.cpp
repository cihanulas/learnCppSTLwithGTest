#include "pch.h"

#include "BuilderPattern.h"
#include "gmock\gmock.h"
using namespace testing;

TEST(TestBuilderPattern, CreateMeals) {
  MealBuilder mealBuilder = MealBuilder();

  Meal vegMeal = mealBuilder.VegMeal();
  EXPECT_EQ(vegMeal.getCost(), 13);
  ASSERT_THAT(vegMeal.item_names_in_the_meal(),
              ElementsAre("Veg Burger", "Coke"));

  Meal nonVegMeal = mealBuilder.NonVegMeal();
  EXPECT_EQ(nonVegMeal.getCost(), 23);
  ASSERT_THAT(nonVegMeal.item_names_in_the_meal(),
              ElementsAre("Chicken Burger", "Pepsi"));
}
