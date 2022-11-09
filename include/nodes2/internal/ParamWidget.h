/**
 * @file ParamWidget.h
 * @author moth (QianMoth@qq.com)
 * @brief 节点属性控件创建
 * @version 0.1
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <QScrollArea>
#include <QVBoxLayout>
#include <QJsonObject>

#include "Export.hpp"

namespace QtNodes
{
    class BaseNode;
    class Parameter;

    /**
     * @brief 嵌入式窗体
     * 所有自定义控件都将添加到ParamWidget
     *
     */
    class FLOW_EDITOR_PUBLIC ParamWidget : public QScrollArea
    {
        Q_OBJECT
    public:
        ParamWidget(BaseNode *node, QWidget *parent = nullptr);
        void save(QJsonObject &json);          // node内控件参数的保存
        void restore(QJsonObject const &json); // node内控件参数的恢复

    private:
        /**
         * @brief Create a Widgets object
         *
         */
        void createWidgets();

        template <typename T>
        void createParamSlider(Parameter *p, QBoxLayout *hbl);
        template <typename T>
        void createParamTrackEditX(Parameter *p, QBoxLayout *hbl);
        template <typename T>
        void createParamTrackEditXY(Parameter *p, QBoxLayout *hbl);
        template <typename T>
        void createParamTrackEditXYZ(Parameter *p, QBoxLayout *hbl);
        template <typename T>
        void createParamTrackEditXYZW(Parameter *p, QBoxLayout *hbl);
        void createParamRGBA(Parameter *p, QBoxLayout *hbl);

        void createParamLabel(Parameter *p, QBoxLayout *hbl);

        void createParamButton(Parameter *p, QBoxLayout *hbl);
        void createParamBoolButton(Parameter *p, QBoxLayout *hbl);
        void createParamFlags(Parameter *p, QBoxLayout *hbl);
        void createParamEnum(Parameter *p, QBoxLayout *hbl);

        void createParamLineEdit(Parameter *p, QBoxLayout *hbl);
        void createParamLineEditShow(Parameter *p, QBoxLayout *hbl);
        void createParamText(Parameter *p, QBoxLayout *hbl);
        void createParamFile(Parameter *p, QBoxLayout *hbl);
        void createParamFileSave(Parameter *p, QBoxLayout *hbl);

        void createParamImage(Parameter *p, QBoxLayout *hbl);

        QVBoxLayout *_layout;
        BaseNode *_node;
    };
} // QtNodes
