/**
 * @file Color.h
 * @author moth (QianMoth@qq.com)
 * @brief 自定义颜色数据类型
 * @version 0.1
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "Types.h"

#include "Export.hpp"

namespace QtNodes
{

  enum eColorConst
  {
    eCOL_RED,
    eCOL_GREEN,
    eCOL_BLUE,
    eCOL_ORANGE,
    eCOL_YELLOW,
    eCOL_PURPLE,
    eCOL_CYAN,
    eCOL_PINK,
    eCOL_WHITE,
    eCOL_BLACK,
    eCOL_GRAY,
    eCOL_DARKGRAY,
    eCOL_LIGHTGRAY,
  };

  // 8-bit per channel integer color
  class FLOW_EDITOR_PUBLIC eColor
  {
  public:
    eColor();
    eColor(uint8_t nr, uint8_t ng, uint8_t nb, uint8_t na = 255);
    eColor(eColorConst cc);

    void set(uint8_t nr, uint8_t ng, uint8_t nb);
    void set(uint8_t nr, uint8_t ng, uint8_t nb, uint8_t na);
    uint8_t grayScale() const;
    void toGrayScale();
    void scale(const eColor &c);
    void minComponents(const eColor &c);
    void maxComponents(const eColor &c);
    void average(const eColor &c);
    void difference(const eColor &c);
    eColor lerp(const eColor &to, double t) const;
    uint32_t toArgb() const;

    eColor operator+(const eColor &c) const;
    eColor operator-(const eColor &c) const;
    eColor operator*(double s) const;
    eColor &operator+=(const eColor &c);
    eColor &operator-=(const eColor &c);
    eColor &operator*=(double s);
    uint8_t &operator[](int index);
    bool operator==(const eColor &c) const;
    bool operator!=(const eColor &c) const;

    const uint8_t &operator[](int index) const;

    friend eColor operator*(double s, const eColor &c) { return c * s; }

  public:
    // non-inlinable functions
    void toHsv(int &h, int &s, int &v);
    void fromHsv(int h, int s, int v);

  public:
    union
    {
      struct
      {
        uint8_t r; // LSB
        uint8_t g;
        uint8_t b;
        uint8_t a; // MSB
      };

      uint32_t abgr;
    };
  };

} // QtNodes
