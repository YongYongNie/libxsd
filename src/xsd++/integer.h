/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_INTEGER_H
#define XSDXX_INTEGER_H

#include "decimal.h"

#include <cstdint> /* for INTMAX_*, std::intmax_t */
#include <string>  /* for std::to_string() */

namespace xsd {
  class integer;
}

class xsd::integer : public xsd::decimal {
public:
  using value_type = std::intmax_t;

  static constexpr char name[]    = "integer";
  static constexpr char pattern[] = "^([-+])?0*([0-9]+)$";
  static constexpr bool captures  = 3;

  static value_type parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static value_type parse(const char* literal);

  static value_type parse(const char* literal, std::error_condition& error) noexcept;

  static bool match(const std::string& literal) noexcept {
    return match(literal.c_str());
  }

  static bool match(const char* literal) noexcept;

  integer(int literal)
    : decimal{std::to_string(literal)} {}

  integer(unsigned int literal)
    : decimal{std::to_string(literal)} {}

  integer(long literal)
    : decimal{std::to_string(literal)} {}

  integer(unsigned long literal)
    : decimal{std::to_string(literal)} {}

  integer(long long literal)
    : decimal{std::to_string(literal)} {}

  integer(unsigned long long literal)
    : decimal{std::to_string(literal)} {}

  integer(const std::string& literal)
    : decimal{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;

  std::intmax_t as_integer(
    std::intmax_t min_value = INTMAX_MIN,
    std::intmax_t max_value = INTMAX_MAX) const;
};

#endif /* XSDXX_INTEGER_H */
