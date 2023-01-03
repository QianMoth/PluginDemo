/**
 * @file TextModel.hpp
 * @author moth (QianMoth@qq.com)
 * @brief string
 * @version 1.0.0
 * @date 2022-12-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <QGridLayout>
#include <QTextEdit>
#include <QtNodes/NodeDelegateModel>
#include <QtNodes/NodeDelegateModelRegistry>
#include <data/BaseData.hpp>
#include <iostream>

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class TextModel : public QtNodes::NodeDelegateModel
{
    Q_OBJECT

  public:
    TextModel();
    virtual ~TextModel();

  public:
    QString caption() const override { return QString("Text"); }

    bool captionVisible() const override { return false; }

    QString name() const override { return QString("TextModel"); }

  public:
    unsigned int nPorts(PortType const portType) const override;

    NodeDataType dataType(PortType const portType, PortIndex const index) const override;

    std::shared_ptr<NodeData> outData(PortIndex const index) override;

    void setInData(std::shared_ptr<NodeData> nodeData, PortIndex const index) override;

    QWidget *embeddedWidget() override;

    bool resizable() const override { return true; }

  private:
    QWidget *widget = nullptr;
    QGridLayout *_layout = nullptr;
    QTextEdit *_messageBox = nullptr;

  private:
    std::shared_ptr<StringData> _out0;
};
