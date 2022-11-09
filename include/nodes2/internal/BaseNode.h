/**
 * @file BaseNode.h
 * @author moth (QianMoth@qq.com)
 * @brief Node的基类
 * @version 0.1
 * @date 2022-09-26
 *
 * @note
 * @link https://github.com/fredakilla/spkgen.git
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "ParamWidget.h"
#include "Parameter.h"
#include "Types.h"
#include "DataBase.hpp"
#include <nodes/NodeDataModel>

#include "Export.hpp"

namespace QtNodes
{
  /**
   * @brief 输入输出接口
   *
   */
  struct ePort
  {
    PortType type; // 端口种类 输入，输出
    NodeDataType dataType;
    QString id;
    QString name;
    std::shared_ptr<NodeData> data;

    ePort() {}

    ePort(PortType type, QString id, QString name)
        : type(type), id(id), name(name), dataType{id, name}
    {
    }
  };

#pragma region /* 添加输入输出接口 */

#define IN_PORT(dataid, dataname) \
  _inputs.push_back(new QtNodes::ePort(PortType::In, QString(dataid), QString(dataname)));

#define OUT_PORT(dataid, dataname) \
  _outputs.push_back(new QtNodes::ePort(PortType::Out, QString(dataid), QString(dataname)));

#pragma endregion

#pragma region /* 添加自定义参数,对应生成控件 */

#define PARAM_TEXT(name, label) \
  addParameter<QString>(QtNodes::EPT_TEXT, name, 0, 0, QString(label));

#define PARAM_STRING(name, label) \
  addParameter<QString>(QtNodes::EPT_STRING, name, 0, 0, QString(label));

#define PARAM_STRINGSHOW(name, label) \
  addParameter<QString>(QtNodes::EPT_STRINGSHOW, name, 0, 0, QString(label));

/* 打开文件 */
#define PARAM_FILE(name, path) \
  addParameter<QString>(QtNodes::EPT_FILE, name, 0, 0, QString(path));

/* 保存文件 */
#define PARAM_FILESAVE(name, path) \
  addParameter<QString>(QtNodes::EPT_FILESAVE, name, 0, 0, QString(path));

#define PARAM_BOOL(name, boolean) \
  addParameter<bool>(QtNodes::EPT_BOOL, name, 0, 0, (bool)boolean);

#define PARAM_BUTTON(name, label) \
  addParameter<QString>(QtNodes::EPT_BUTTON, name, 0, 0, QString(label));

#define PARAM_SLIDER(name, min, max, v) \
  addParameter<int>(QtNodes::EPT_SLIDER, name, min, max, (int)v);

#define PARAM_DSLIDER(name, min, max, v) \
  addParameter<double>(QtNodes::EPT_DSLIDER, name, min, max, (double)v);

#define PARAM_INT(name, min, max, v) \
  addParameter<int>(QtNodes::EPT_INT, name, min, max, (int)v);

#define PARAM_IXY(name, min, max, x, y) \
  addParameter<QtNodes::eIXY>(QtNodes::EPT_IXY, name, min, max, QtNodes::eIXY((int)x, (int)y));

#define PARAM_IXYZ(name, min, max, x, y, z)                       \
  addParameter<QtNodes::eIXYZ>(QtNodes::EPT_IXYZ, name, min, max, \
                               QtNodes::eIXYZ((int)x, (int)y, (int)z));

#define PARAM_IXYZW(name, min, max, x, y, z, w)                     \
  addParameter<QtNodes::eIXYZW>(QtNodes::EPT_IXYZW, name, min, max, \
                                QtNodes::eIXYZW((int)x, (int)y, (int)z, (int)w));

#define PARAM_FLOAT(name, min, max, f) \
  addParameter<double>(QtNodes::EPT_FLOAT, name, min, max, (double)f);

#define PARAM_FXY(name, min, max, x, y) \
  addParameter<QtNodes::eFXY>(EPT_FXY, name, min, max, eFXY((double)x, (double)y));

#define PARAM_FXYZ(name, min, max, x, y, z)                       \
  addParameter<QtNodes::eFXYZ>(QtNodes::EPT_FXYZ, name, min, max, \
                               QtNodes::eFXYZ((double)x, (double)y, (double)z));

#define PARAM_FXYZW(name, min, max, x, y, z, w)            \
  addParameter<QtNodes::eFXYZW>(EPT_FXYZW, name, min, max, \
                                QtNodes::eFXYZW((double)x, (double)y, (double)z, (double)w));

/* 列表选择，最多256个 */
#define PARAM_ENUM(name, descr, index)                            \
  addParameter<int>(QtNodes::EPT_ENUM, name, 0, 255, (int)index); \
  _parameters.back()->setDescription(descr);

#define PARAM_FLAGS(name, descr, index)                         \
  addParameter<unsigned char>(QtNodes::EPT_FLAGS, name, 0, 255, \
                              (unsigned char)(index));          \
  _parameters.back()->setDescription(descr);

#define PARAM_RGBA(name, r, g, b, a) \
  addParameter<QtNodes::eColor>(QtNodes::EPT_RGBA, name, 0, 255, QtNodes::eColor(r, g, b, a));

#define PARAM_IMAGE(name, pixmap) \
  addParameter<QPixmap>(QtNodes::EPT_IMAGE, name, 0, 0, QPixmap(pixmap));

#pragma endregion

  /**
   * @brief 所有node的基础类
   *
   */
  class FLOW_EDITOR_PUBLIC BaseNode : public NodeDataModel
  {
    Q_OBJECT

  public:
    BaseNode();
    virtual ~BaseNode();
    virtual void init() { process(); }
    virtual int process(const Parameter &param = Parameter()) { return 0; }
    virtual bool resizable() const override { return false; } // 支持改变node大小

    size_t getParameterCount() const;                  // 控件计数
    Parameter *getParameter(const unsigned int index); // 通过索引值获取控件
    Parameter *getParameter(const QString name);       // 通过名字获取控件

  protected:
    virtual const QString Name() const = 0;
    QString name() const override { return Name(); }
    QString caption() const override { return Name(); }
    virtual bool captionVisible() const override { return true; }
    virtual bool portCaptionVisible(PortType, PortIndex) const override
    {
      return true;
    }
    QString portCaption(PortType portType, PortIndex portIndex) const override;
    unsigned int nPorts(PortType portType) const override;
    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
    void setInData(std::shared_ptr<NodeData> nodeData, PortIndex portIndex) override;
    virtual QWidget *embeddedWidget() override { return _paramWidget; }
    void createParamWidgets() { _paramWidget = new ParamWidget(this); }

    template <typename T>
    void addParameter(ParamType type, QString name, double min, double max, T value)
    {
      Parameter *p = new Parameter(type, name, min, max, this);
      p->baseValue = (T)value;
      _parameters.push_back(p);
    }

    template <class T>
    std::shared_ptr<T> getInput(unsigned int portIndex)
    {
      assert(portIndex < _inputs.size());
      assert(_inputs[portIndex]->name == T::metatype());
      std::shared_ptr<T> ptr =
          std::dynamic_pointer_cast<T>(_inputs[portIndex]->data);
      return ptr;
    }

  protected:
    std::vector<ePort *> _inputs;  // 输入接口集合
    std::vector<ePort *> _outputs; // 输出接口集合
    ParamWidget *_paramWidget;
    std::vector<Parameter *> _parameters;

  protected:
    NodeValidationState modelValidationState = NodeValidationState::Valid;
    QString modelValidationError = QString("ok");
    NodeValidationState validationState() const override;
    QString validationMessage() const override;
    void setValidationState(NodeValidationState state, const QString &msg = "")
    {
      modelValidationState = state;
      modelValidationError = msg;
    }

    QJsonObject save() const override
    {
      QJsonObject modelJson = NodeDataModel::save();

      if (_paramWidget)
        _paramWidget->save(modelJson);

      return modelJson;
    }

  public:
    void restore(QJsonObject const &p) override
    {
      if (_paramWidget)
        _paramWidget->restore(p);
    }

  public Q_SLOTS:
    virtual void onParameterChanged(const Parameter &param)
    {
      if (process(param) == 0)
      {
        Q_EMIT dataUpdated(0);
      }
    }
  };

} // QtNodes
