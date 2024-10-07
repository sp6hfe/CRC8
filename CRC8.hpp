/**
 * @file CRC8.hpp
 * @author Grzegorz Kaczmarek SP6HFE
 * @brief
 * @version 0.1
 * @date 2024-10-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <stdint.h>

namespace crc {

class CRC8 {
public:
  /**
   * @brief Constructor
   *
   * @param polynomial Used polynimial
   * @param initValue Algorithm initialization value
   */
  CRC8(uint8_t polynomial, uint8_t initValue) : _polynomial(polynomial), _initValue(initValue) { init(); }

  /// Deleted copy constructor
  CRC8(const CRC8&) = delete;

  /// Deleted move constructor
  CRC8(CRC8&&) = delete;

  /// Deleted copy assignment
  CRC8& operator=(const CRC8&) = delete;

  /// Deleted move assignment
  CRC8& operator=(CRC8&&) = delete;

  /// @brief Default destructor
  ~CRC8() = default;

  /**
   * @brief Re-initialize CRC calculation algorithm
   *
   * @note Useful when this object is used multiple times
   */
  void init() { _crc = _initValue; }

  /**
   * @brief Update CRC value
   *
   * @param data Data covered by CRC checksum
   */
  void update(const uint8_t data) {
    // step 1: XOR with the data value
    _crc ^= data;

    // step 2: shift left 8 times and on each stage if MSb is 1 then XOR with polynomial
    for (auto bitNo{8U}; bitNo > 0; --bitNo) {
      if (_crc & 0x80) {
        _crc = ((_crc << 1U) ^ _polynomial);
      } else {
        _crc <<= 1U;
      }
    }
  }

  /**
   * @brief Get calculated CRC8
   *
   * @return The CRC
   */
  uint8_t get() { return _crc; }

private:
  /// @brief Used polynomial
  uint8_t _polynomial;

  /// @brief Algorithm initialization value
  uint8_t _initValue;

  /// @brief Calculated CRC
  uint8_t _crc{0U};
};

}  // namespace crc
