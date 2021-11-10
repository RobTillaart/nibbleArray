//
//    FILE: nibbleArray.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
// PURPOSE: Arduino library for a compact array of nibbles (4 bits)
//     URL: https://github.com/RobTillaart/nibbleArray
//
//  HISTORY:
//  0.1.0   2015-04-12  initial version
//  0.2.0   2020-06-21  refactor; #pragma once; removed pre 1.0 support
//  0.2.1   2020-01-02  Arduino-CI + unit test
//  0.2.2   2020-11-10  update Arduino-CI, badges
//                      add getMaxSize();
//                      fix bug in setAll();
//                      add memory();


#include "nibbleArray.h"


nibbleArray::nibbleArray(uint16_t size)
{
  _size = min(NIBBLEARRAY_MAXSIZE, size);
  _bytes = (_size + 1)/2;
  arr = (uint8_t *) malloc(_bytes);
}


nibbleArray::~nibbleArray()
{
  if (arr != NULL)
  {
    free(arr);
  }
}


uint8_t nibbleArray::get(const uint16_t idx)
{
  if (idx > _size)
  {
    return NIBBLEARRAY_ERROR_INDEX; // disable this check for more speed
  }
  if (idx & 1) return arr[idx/2] & 0x0F;
  return arr[idx/2] >> 4;
}


uint8_t nibbleArray::set(const uint16_t idx, uint8_t value)
{
  if (idx > _size)
  {
    return NIBBLEARRAY_ERROR_INDEX; // disable this check for more speed
  }
  uint8_t v = value & 0x0F;
  if (idx & 1) arr[idx/2] = (arr[idx/2] & 0xF0) | v;
  else arr[idx/2] = (arr[idx/2] & 0x0F) | (v << 4);
  return NIBBLEARRAY_OK;
}


void nibbleArray::clear()
{
  memset(arr, 0, (_size + 1)/2);
}


void nibbleArray::setAll(uint8_t value)
{
  uint8_t v = value & 0x0F;
  v |= (v << 4);
  memset(arr, v, (_size + 1)/2);
}

// -- END OF FILE --
