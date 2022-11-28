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

#include <nodes/NodeDataModel>
#include <nodes/NodeData>

#include "Parameter.h"

#include <QObject>
#include <QString>

#include "Export.hpp"

namespace QtNodes
{

  enum class PortType;

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

  class NodeDataModel;

  enum class NodeValidationState;
  using PortIndex = int;

  // class Parameter;
  class ParamWidget;

  /**
   * @brief 所有node的基础类
   *
   */
  class FLOW_EDITOR_PUBLIC BaseNode : public NodeDataModel
  {
    // Q_OBJECT

  public:
    BaseNode();
    virtual ~BaseNode();
    void init();                                  ///< 初始化
    virtual bool initProcess();                   ///< 可以重写的初始化
    virtual void process(const Parameter &param); ///< return PortIndex
    virtual bool resizable() const;               ///< 支持改变node大小

    size_t getParameterCount() const;                  ///< 控件计数
    Parameter *getParameter(const unsigned int index); ///< 通过索引值获取控件
    Parameter *getParameter(const QString name);       ///< 通过名字获取控件

    QJsonObject save() const;
    void restore(QJsonObject const &p);

  public Q_SLOTS:
    virtual void onParameterChanged(const Parameter &param);

  protected:
    virtual const QString Name() const = 0;
    QString name() const;
    QString caption() const;
    virtual bool captionVisible() const;
    virtual bool portCaptionVisible(PortType, PortIndex) const;
    QString portCaption(PortType portType, PortIndex portIndex) const;
    unsigned int nPorts(PortType portType) const;
    NodeDataType dataType(PortType portType, PortIndex portIndex) const;
    bool setOutData(const PortIndex portIndex);
    void setInData(std::shared_ptr<NodeData> nodeData, PortIndex portIndex);
    virtual QWidget *embeddedWidget();
    void createParamWidgets();

    template <typename T>
    void addParameter(int type, QString name, double min, double max, T value)
    {
      Parameter *p = new Parameter(type, name, min, max, this);
      p->baseValue = (T)value;
      _parameters.push_back(p);
    }

    template <class T>
    std::shared_ptr<T> getInput(unsigned int portIndex) const
    {
      assert(portIndex < _inputs.size());
      assert(_inputs[portIndex]->name == T::metatype());
      std::shared_ptr<T> ptr =
          std::dynamic_pointer_cast<T>(_inputs[portIndex]->data);
      return ptr;
    }

  protected:
    std::vector<ePort *> _inputs;  ///< 输入接口集合
    std::vector<ePort *> _outputs; ///< 输出接口集合
    ParamWidget *_paramWidget;
    std::vector<Parameter *> _parameters;

  protected:
    NodeValidationState modelValidationState; // NodeValidationState::Valid;
    QString modelValidationError = QString("ok");
    NodeValidationState validationState() const;
    QString validationMessage() const;
    void setValidationState(NodeValidationState state, const QString &msg = "");
  };

#pragma region /* 添加输入输出接口 */

#define IN_PORT(dataid, dataname) \
  _inputs.push_back(new QtNodes::ePort(PortType::In, QString(dataid), QString(dataname)));

#define OUT_PORT(dataid, dataname) \
  _outputs.push_back(new QtNodes::ePort(PortType::Out, QString(dataid), QString(dataname)));

#pragma endregion /* 添加输入输出接口 */

#pragma region /* 添加自定义参数,对应生成控件 */

#define PARAM_TEXT(name, label) \
  addParameter<QString>(QtNodes::EPT_TEXT, name, 0, 0, QString(label));

#define PARAM_TEXTSHOW(name, label) \
  addParameter<QString>(QtNodes::EPT_TEXT | QtNodes::EPT_SHOWONLY, name, 0, 0, QString(label));

#define PARAM_STRING(name, label) \
  addParameter<QString>(QtNodes::EPT_STRING, name, 0, 0, QString(label));

#define PARAM_STRINGSHOW(name, label) \
  addParameter<QString>(QtNodes::EPT_STRING | QtNodes::EPT_SHOWONLY, name, 0, 0, QString(label));

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

#define PARAM_INTSHOW(name, min, max, v) \
  addParameter<int>(QtNodes::EPT_INT | QtNodes::EPT_SHOWONLY, name, min, max, (int)v);

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

} // QtNodes
