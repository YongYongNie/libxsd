/* This is free and unencumbered software released into the public domain. */

#ifndef XSDXX_DATETIME_H
#define XSDXX_DATETIME_H

#include "value.h"

#include <cstdint> /* for std::int64_t */

namespace xsd {
  class datetime;
}

class xsd::datetime : public xsd::value {
public:
  using value_type = std::int64_t;

  static constexpr char name[]    = "dateTime";
  static constexpr char pattern[] = "^(-)?([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2})(\\.[0-9]+)?(Z|([-+][0-9]{2}:[0-9]{2}))?$";
  static constexpr bool captures  = 10;

  static value_type parse(const std::string& literal) {
    return parse(literal.c_str());
  }

  static value_type parse(const char* literal);

  static value_type parse(const char* literal, std::error_condition& error) noexcept;

  static bool match(const std::string& literal) noexcept {
    return match(literal.c_str());
  }

  static bool match(const char* literal) noexcept;

  datetime(const std::string& literal)
    : xsd::value{literal} {}

  virtual bool validate() const noexcept override;

  virtual bool canonicalize() noexcept override;

  value_type value() const;

  value_type value(std::error_condition& error) const noexcept;
};

#endif /* XSDXX_DATETIME_H */
