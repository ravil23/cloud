#pragma once

namespace cloud {
namespace utils {

/**
 * \brief Convert string to other type.
 * \tparam     T  Result type.
 * \param[in]  s  Input string.
 * \return  Converted value.
 */
template <class T>
T lexical_cast(const std::string& s) {
  std::stringstream ss(s);
  T result;
  if ((ss >> result).fail() || !(ss >> std::ws).eof()) {
      throw std::bad_cast();
  }
  return result;
}

} // namespace utils
} // namespace cloud
