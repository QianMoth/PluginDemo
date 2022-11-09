/**
 * @file Types.h
 * @author moth (QianMoth@qq.com)
 * @brief 自定义数据类型
 * @version 0.1
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <assert.h>
#include <math.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>

namespace QtNodes
{
  template <class T>
  T eLerp(const T &a, const T &b, double t)
  {
    // 颜色渐变
    return a + (b - a) * t;
  }

  template <class T>
  bool eGetBit(T t, uint32_t index)
  {
    assert(index < sizeof(T) * 8);
    return ((t & (1 << index)) != 0);
  }

  template <class T>
  void eToggleBit(T &t, uint32_t index)
  {
    assert(index < sizeof(T) * 8);
    t ^= (1 << index);
  }

} // QtNodes
