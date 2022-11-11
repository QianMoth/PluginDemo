/**
 * @file Parameter.h
 * @author moth (QianMoth@qq.com)
 * @brief
 * @version 0.1
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>

#include <variant>

// #include "Types.h"
#include "Color.h"
#include "DataBase.h"

#include "Export.hpp"

namespace QtNodes
{

    class BaseNode;

    /**
     * @brief 参数类，代表着不同的控件
     * EPT - Enum Param Type
     *
     */
    enum ParamType
    {
        EPT_NONE = 0, // 无控件
        EPT_BOOL,     // 开关
        EPT_BUTTON,   // 按钮
        EPT_FLAGS,    // 多选按钮
        EPT_ENUM,     // 列表选择

        EPT_FLOAT,   // 1个浮点数
        EPT_FXY,     // 2个浮点数
        EPT_FXYZ,    // 3个浮点数
        EPT_FXYZW,   // 4个浮点数
        EPT_INT,     // 1个整数
        EPT_IXY,     // 2个整数
        EPT_IXYZ,    // 3个整数
        EPT_IXYZW,   // 4个整数
        EPT_RGB,     // 颜色(无透明度)
        EPT_RGBA,    // 颜色(有透明度)
        EPT_SLIDER,  // 整数滑块
        EPT_DSLIDER, // 浮点数滑块

        EPT_STRING,   // 单行文本框
        EPT_TEXT,     // 多行文本
        EPT_FILE,     // 打开文件
        EPT_FILESAVE, // 保存文件

        EPT_IMAGE, // 图像显示

        EPT_SHOWONLY = 0x02000000, // 表示该控件仅仅用于显示
    };

    //  possible variant type for parameters
    typedef std::variant<double, int, bool, unsigned char,
                         eFXY, eFXYZ, eFXYZW,
                         eIXY, eIXYZ, eIXYZW,
                         QString, QPixmap, eColor>
        eParamValue;

    class FLOW_EDITOR_PUBLIC Parameter : public QObject
    {
        Q_OBJECT
    public:
        int type;     // ParamType
        QString name; // 参数名
        double min;   // 参数最小值
        double max;   // 参数最大值
        BaseNode *node;
        bool isConnected;
        eParamValue baseValue;
        const eParamValue defVal;
        QString m_descr; // used for enum and flags texts

    public:
        Parameter();
        Parameter(int type, QString name, double min, double max, BaseNode *node);

        // unsigned int getComponentCount();
        void setDescription(const QString &descr);
        const QString &getDescription() const;
        int getType();
        double getMin() const;
        double getMax() const;
        BaseNode *getOwnerOp() const;
        void setChanged(bool reconnect = false);
        const eParamValue &getDefaultValue() const;
        eParamValue &getBaseValue();
        const eParamValue &getBaseValue() const;

        template <typename T>
        T getValue() const
        {
            return std::get<T>(baseValue);
        }

        template <typename T>
        int setValue(const T value)
        {
            try
            {
                if (auto v = std::get_if<T>(&baseValue))
                {
                    *v = value;
                    Q_EMIT(this->parameterUpdated()); // 值改变后发送信号，使得控件同步更新
                    return 0;
                }
                return -1;
            }
            catch (...)
            {
                return -1;
            }
        }

        bool getValueAsBool() const;
        int getValueAsEnum() const;
        unsigned char getValueAsFlags() const;
        QString getValueAsString() const;
        double getValueAsFloat() const;
        eFXY getValueAsFXY() const;
        eFXYZ getValueAsFXYZ() const;
        eFXYZW getValueAsFXYZW() const;
        int getValueAsInt() const;
        eIXY getValueAsIXY() const;
        eIXYZ getValueAsIXYZ() const;
        eIXYZW getValueAsIXYZW() const;
        eColor getValueAsColor() const;

    Q_SIGNALS:
        void parameterUpdated(); // 参数改变信号，可以和控件显示绑定
        void widgetUpdated();
    };

#endif // PARAMETER_H

} // QtNodes
