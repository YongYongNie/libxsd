/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "const.h" /* for XSD_DOUBLE_CAPTURES */
#include "double.h"
#include "regex.h" /* for std::regex, std::regex_match() */

#include <cerrno>  /* for ERANGE, errno */
#include <cstdlib> /* for std::strtod() */

using namespace std::regex_constants;
using namespace xsd;

////////////////////////////////////////////////////////////////////////////////

constexpr char double_::name[];

constexpr char double_::pattern[];

static const std::regex double_regex{double_::pattern};

double
double_::parse(const char* literal) {
  std::error_condition error;
  const auto value = parse(literal, error);

  if (error) {
    if (error == std::errc::invalid_argument) {
      throw std::invalid_argument{literal};
    }
    if (error == std::errc::result_out_of_range) {
      if (value == 0.0) {
        throw std::underflow_error{literal};
      }
      else {
        throw std::overflow_error{literal};
      }
    }
  }

  return value;
}

double
double_::parse(const char* literal,
               std::error_condition& error) noexcept {
  if (!match(literal)) {
    error = std::errc::invalid_argument;
    return 0.0;
  }

  const char* endptr = nullptr;
  errno = 0;
  const double value = std::strtod(literal, (char**)&endptr);

  if (errno == ERANGE) {
    error = std::errc::result_out_of_range;
    return value;
  }

  return value;
}

bool
double_::match(const char* literal) noexcept {
  return std::regex_match(literal, double_regex, match_not_null);
}

bool
double_::validate() const noexcept {
  return double_::match(_literal);
}

bool
double_::canonicalize() noexcept {
  return false; // TODO
}

double_::operator double() const {
  std::error_condition error;
  const auto result = value(error);
  if (error) throw std::bad_cast{};
  return result;
}

double_::operator float() const {
  return operator double(); /* loss of precision */
}

double
double_::value() const {
  return parse(c_str());
}

double
double_::value(std::error_condition& error) const noexcept {
  return parse(c_str(), error);
}
