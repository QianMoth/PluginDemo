/**
 * @file CustomFlowScene.h
 * @author moth (QianMoth@qq.com)
 * @brief 自定义Scene，多了几个快捷键
 * @version 0.1
 * @date 2022-09-24
 *
 * @note
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#include <nodes/DataModelRegistry>
#include <nodes/FlowScene>
// #include <nodes/NodeDataModel>
#include <nodes/Node>

#include "Export.hpp"

namespace QtNodes
{

  class BaseNode;

  /**
   * @brief 场景（画布），所有节点在Scene上绘制
   *
   */
  class FLOW_EDITOR_PUBLIC CustomFlowScene : public FlowScene
  {
    Q_OBJECT

  public:
    CustomFlowScene(std::shared_ptr<DataModelRegistry> registry,
                    QObject *parent = Q_NULLPTR);
    CustomFlowScene(QObject *parent = Q_NULLPTR);
    ~CustomFlowScene();

    void save(QJsonObject &json) const;
    void load(const QJsonObject &json);

  Q_SIGNALS:
    void modified();

  public Q_SLOTS:

  private Q_SLOTS:
    void showNode(Node &node);
    void initNode(Node &node);
    void nodeContextMenu(Node &node, const QPointF &pos);

  private:
    void _initialize();
    void _copyNode(Node &node);

  private:
    QMenu *_editMenu = Q_NULLPTR;
  };

} // QtNodes
