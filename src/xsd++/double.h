/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DOUBLE_H
#define XSDXX_DOUBLE_H

#include "value.h"

#include <string> /* for std::to_string() */

namespace xsd {
  class double_;
}

class xsd::double_ : public xsd::value {
public:
  using value_type = double;

  static constexpr char name[]    = "double";
  static constexpr char pattern[] = "^([-+])?0*([0-9]*)\\.?(0*[0-9]*)0*[Ee]?([-+])?0*([0-9]*)?$";
  static constexpr bool captures  = 6;

  static value_type parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static value_type parse(const char* literal);

  static value_type parse(const char* literal, std::error_condition& error) noexcept;

  static bool match(const std::string& literal) noexcept {
    return match(literal.c_str());
  }

  static bool match(const char* literal) noexcept;

  double_(float literal)
    : value{std::to_string(literal)} {}

  double_(double literal)
    : value{std::to_string(literal)} {}

  double_(long double literal)
    : value{std::to_string(static_cast<double>(literal))} {}

  double_(const std::string& literal)
    : value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;
};

#endif /* XSDXX_DOUBLE_H */
