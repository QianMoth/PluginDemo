/**
 * @file CustomWidgets.h
 * @author moth (QianMoth@qq.com)
 * @brief 节点内自定义控件
 * @version 0.1
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#ifndef PARAM_WIDGETS_HPP
#define PARAM_WIDGETS_HPP

#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QPushButton>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QVariant>

#include "Parameter.h"

#include "Export.hpp"

namespace QtNodes
{

    /**
     * @brief 数字Box
     *
     */
    class eNumBox : public QDoubleSpinBox
    {
        Q_OBJECT
    public:
        eNumBox(double &value, double min, double max, QWidget *parent);
        eNumBox(int &value, int min, int max, QWidget *parent);
        eNumBox(uint8_t &value, uint8_t min, uint8_t max, QWidget *parent);

    private Q_SLOTS:
        void _onValueChanged(double val);

    private:
        int *_intRef;
        double *_doubleRef;
        uint8_t *_u8Ref;
    };

    /**
     * @brief 数字类型的控件
     *
     */
    class FLOW_EDITOR_PUBLIC eParamNumEdit : public eNumBox
    {
        Q_OBJECT
    public:
        eParamNumEdit(int &value, Parameter &param, QWidget *parent = nullptr);
        eParamNumEdit(double &value, Parameter &param, QWidget *parent = nullptr);
        eParamNumEdit(uint8_t &value, Parameter &param, QWidget *parent = nullptr);

        void setIndicatorColor(const QColor &indCol);
        void setIndicatorEnabled(bool indEnabled);

        virtual void paintEvent(QPaintEvent *pe);

    public Q_SLOTS:
        void _updateParameters();
    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _onValueChanged();

    private:
        Parameter &m_param;
        QColor m_indCol;
        bool m_indEnabled;
    };

    /**
     * @brief 按钮
     *
     */
    class FLOW_EDITOR_PUBLIC eButton : public QPushButton
    {
        Q_OBJECT
    public:
        eButton(Parameter &param, QWidget *parent = nullptr);
    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _onClicked();

    private:
        Parameter &m_param;
    };

    /**
     * @brief 开关
     *
     */
    class FLOW_EDITOR_PUBLIC eBoolButton : public QToolButton
    {
        Q_OBJECT
    public:
        eBoolButton(Parameter &param, QWidget *parent = nullptr);
        void setClicked(bool clicked = false);
    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _updateCaption();
        void _onClicked();

    private:
        Parameter &m_param;
    };

    /**
     * @brief comboBox
     *
     */
    class FLOW_EDITOR_PUBLIC eComboBox : public QComboBox
    {
        Q_OBJECT
    public:
        eComboBox(Parameter &param, QWidget *parent = nullptr);
    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _updateSelection();
        void _onActivated(int index);

    private:
        Parameter &m_param;
    };

    /**
     * @brief 多选开关
     *
     */
    class FLOW_EDITOR_PUBLIC eFlagButton : public QToolButton
    {
        Q_OBJECT
    public:
        eFlagButton(Parameter &param, const QString &caption, uint32_t flagIndex, QWidget *parent = nullptr);
    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _updateDownState();
        void _onClicked();

    private:
        Parameter &m_param;
        uint32_t m_flagIndex;
    };

    /**
     * @brief 多行文本
     *
     */
    class FLOW_EDITOR_PUBLIC eTextEdit : public QTextEdit
    {
        Q_OBJECT
    public:
        eTextEdit(Parameter &param, QWidget *parent = nullptr);
    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _onTextChanged();

    private:
        Parameter &m_param;
    };

    /**
     * @brief 图像显示
     *
     */
    class FLOW_EDITOR_PUBLIC ePixmapShow : public QLabel
    {
        Q_OBJECT
    public:
        ePixmapShow(Parameter &param, QWidget *parent = nullptr);
    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    public Q_SLOTS:
        void _updateImage();

    protected:
        bool eventFilter(QObject *object, QEvent *event) override;

    private:
        Parameter &m_param;
        QPixmap _pixmap;
    };

    /**
     * @brief 单行文本
     *
     */
    class FLOW_EDITOR_PUBLIC eLineEdit : public QLineEdit
    {
        Q_OBJECT
    public:
        enum Type
        {
            EDIT,
            NOEDIT
        };

        eLineEdit(Parameter &param, Type type = Type::EDIT, QWidget *parent = nullptr);
    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _updateCaption();
        void _onTextChanged(const QString &text);

    private:
        Parameter &m_param;
        Type _type;
    };

    class FLOW_EDITOR_PUBLIC eSliderEdit : public QWidget
    {
        Q_OBJECT
    public:
        eSliderEdit(int &value, Parameter &param, QWidget *parent = nullptr);
        eSliderEdit(double &value, Parameter &param, QWidget *parent = nullptr);
        virtual ~eSliderEdit();

    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);

    private Q_SLOTS:
        void _onValueChanged();
        void _updateParameters();

    private:
        Parameter &m_param;
        QSlider *m_slider;
        eParamNumEdit *m_edit;
    };

    /**
     * @brief 文件框架，加载文件和保存文件
     *
     */
    class FLOW_EDITOR_PUBLIC eFileFrame : public QWidget
    {
        Q_OBJECT
    public:
        enum Type
        {
            OPEN,
            SAVE
        };

        eFileFrame(Parameter &param, Type type, QWidget *parent = nullptr);
        virtual ~eFileFrame();
    Q_SIGNALS:
        void btnClicked();
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _updateCaption();
        void _onSelectLocally();

    private:
        Parameter &m_param;
        eLineEdit *m_lineEdit;
        Type _type;
    };

    /**
     * @brief 颜色框架
     *
     */
    class FLOW_EDITOR_PUBLIC eColorFrame : public QWidget
    {
        Q_OBJECT
    public:
        eColorFrame(Parameter &param, QWidget *parent = nullptr);
        virtual ~eColorFrame();

    private:
        virtual void timerEvent(QTimerEvent *te);
    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _onSelectLocally();
        void _updateEditColors();

    private:
        Parameter &m_param;
        eParamNumEdit *m_edits[4];
    };

    class FLOW_EDITOR_PUBLIC eParamNumXYFrame : public QWidget
    {
        Q_OBJECT
    public:
        eParamNumXYFrame(Parameter &param, QWidget *parent = nullptr);
        virtual ~eParamNumXYFrame();

    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _updateParameters();

    private:
        Parameter &m_param;
        eParamNumEdit *m_edits[2];
    };

    class FLOW_EDITOR_PUBLIC eParamNumXYZFrame : public QWidget
    {
        Q_OBJECT
    public:
        eParamNumXYZFrame(Parameter &param, QWidget *parent = nullptr);
        virtual ~eParamNumXYZFrame();

    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _updateParameters();

    private:
        Parameter &m_param;
        eParamNumEdit *m_edits[3];
    };

    class FLOW_EDITOR_PUBLIC eParamNumXYZWFrame : public QWidget
    {
        Q_OBJECT
    public:
        eParamNumXYZWFrame(Parameter &param, QWidget *parent = nullptr);
        virtual ~eParamNumXYZWFrame();

    Q_SIGNALS:
        void onParameterChanged(const Parameter &param);
    private Q_SLOTS:
        void _updateParameters();

    private:
        Parameter &m_param;
        eParamNumEdit *m_edits[4];
    };

} // QtNodes
#endif // PARAM_WIDGETS_HPP
