/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DECIMAL_H
#define XSDXX_DECIMAL_H

#include "value.h"

#include <cstdint> /* for std::intmax_t */
#include <string>  /* for std::to_string() */
#include <utility> /* for std::pair */

namespace xsd {
  class decimal;
}

class xsd::decimal : public xsd::value {
public:
  using value_type = std::pair<std::intmax_t, std::intmax_t>;

  static constexpr char name[]    = "decimal";
  static constexpr char pattern[] = "^([-+])?0*([0-9]*)\\.?(0*[1-9]*)0*$";
  static constexpr bool captures  = 4;

  static value_type parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static value_type parse(const char* literal);

  static value_type parse(const char* literal, std::error_condition& error) noexcept;

  static bool match(const std::string& literal) noexcept {
    return match(literal.c_str());
  }

  static bool match(const char* literal) noexcept;

  decimal(int literal)
    : value{std::to_string(literal)} {}

  decimal(unsigned int literal)
    : value{std::to_string(literal)} {}

  decimal(long literal)
    : value{std::to_string(literal)} {}

  decimal(unsigned long literal)
    : value{std::to_string(literal)} {}

  decimal(long long literal)
    : value{std::to_string(literal)} {}

  decimal(unsigned long long literal)
    : value{std::to_string(literal)} {}

  decimal(const std::string& literal)
    : value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;
};

#endif /* XSDXX_DECIMAL_H */
