#pragma once

#include <memory>
class Single {
  Single();  // private

 public:
  static Single* getInstance();
  static std::unique_ptr<Single> m_single;
};
