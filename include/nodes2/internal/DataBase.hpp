/**
 * @file DataBase.hpp
 * @author moth (QianMoth@qq.com)
 * @brief 传递的数据
 * @version 0.1
 * @date 2022-09-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <nodes/NodeDataModel>
// #include <opencv2/opencv.hpp>
#include <iostream>

#include "Export.hpp"

namespace QtNodes
{

#pragma region /* 多数据 */
    template <typename T>
    class eXY
    {
    public:
        struct
        {
            T x;
            T y;
        };

        eXY() {}
        eXY(T x, T y) : x(x), y(y) {}
        T &operator[](int index)
        {
            assert(index < 2);
            return ((T *)this)[index];
        }
    };

    template <typename T>
    class eXYZ
    {
    public:
        struct
        {
            T x;
            T y;
            T z;
        };

        eXYZ() {}
        eXYZ(T x, T y, T z) : x(x), y(y), z(z) {}
        T &operator[](int index)
        {
            assert(index < 3);
            return ((T *)this)[index];
        }
    };

    template <typename T>
    class eXYZW
    {
    public:
        struct
        {
            T x;
            T y;
            T z;
            T w;
        };

        eXYZW() {}
        eXYZW(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
        T &operator[](int index)
        {
            assert(index < 4);
            return ((T *)this)[index];
        }
    };

    typedef eXY<double> eFXY;
    typedef eXYZ<double> eFXYZ;
    typedef eXYZW<double> eFXYZW;
    typedef eXY<int> eIXY;
    typedef eXYZ<int> eIXYZ;
    typedef eXYZW<int> eIXYZW;

#pragma endregion /* 多数据 */

#pragma region /* 数据模板类 */
    template <class T, char ID[20], char NAME[20]>
    class MyNodeData : public NodeData
    {
    public:
        MyNodeData() {}
        MyNodeData(T const &data) : _data(data) {}
        NodeDataType type() const override { return _type; }
        static QString metatype() { return _type.name; }
        T _data;

    private:
        static inline NodeDataType _type = {QString::fromUtf8(ID), QString::fromUtf8(NAME)};
    };

#pragma endregion

#pragma region /* 自定义需要传递的数据种类 */

    /**
     * 模板中传递了两个string 第一个是id，第二个是name
     * 其中id表示的是数据的类型，name表示的是数据的种类
     * 比如我是一个pixmap类型的图像
     * 我可以这么表示：<QPixmap，"pixmap","pimage">
     *
     */

    static char CHAR_INT[20] = "int";
    static char CHAR_DOUBLE[20] = "double";
    static char CHAR_BOOL[20] = "bool";
    typedef MyNodeData<int, CHAR_INT, CHAR_INT> IntData;
    typedef MyNodeData<double, CHAR_DOUBLE, CHAR_DOUBLE> DoubleData;
    typedef MyNodeData<bool, CHAR_BOOL, CHAR_BOOL> BoolData;

    /* Qt */
    static char CHAR_QSTRING[20] = "double";
    static char CHAR_QPIXMAP[20] = "pixmap";
    typedef MyNodeData<QString, CHAR_QSTRING, CHAR_QSTRING> StringData;
    typedef MyNodeData<QPixmap, CHAR_QPIXMAP, CHAR_QPIXMAP> PixmapData;

    // /* opencv */
    // typedef MyNodeData<cv::Mat, ENC_MAT> MatData;
    // typedef MyNodeData<std::vector<cv::Vec3f>, ENC_VEC3F> Vec3fData;

#pragma endregion

} // QtNodes