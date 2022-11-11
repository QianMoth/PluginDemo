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

#include <nodes/DataModelRegistry>
#include <nodes/FlowScene>
// #include <nodes/NodeDataModel>
#include <nodes/Node>

#include "CommentGraphicsItem.h"

#include "Export.hpp"

namespace QtNodes
{

  class BaseNode;

  // empty graphic item used as parent container for comments items
  // 用作注释项的父容器的空图形项
  class FLOW_EDITOR_PUBLIC QGraphicsItemLayer : public QGraphicsItem
  {
  public:
    virtual QRectF boundingRect() const override { return QRectF(0, 0, 0, 0); }

    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *,
                       QWidget *) override {}
  };

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

    // void save() const override;
    // void load() override;
    void save(QJsonObject &json) const;
    void load(const QJsonObject &json);
    void clearComments();

    QString getName() { return _name; }
    void setName(QString name) { _name = name; }

  Q_SIGNALS:

  public Q_SLOTS:
    void deleteSelectedComments(); // 删除选中的注释节点

  private Q_SLOTS:
    void showNode(Node &node);
    void initNode(QtNodes::Node &node);

  protected:
    void keyPressEvent(QKeyEvent *event) override;                 // 按键按下事件
    void keyReleaseEvent(QKeyEvent *event) override;               // 按键释放事件
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override; // 鼠标移动事件

  private:
    void _initialize();
    void _copyNode();   // 拷贝
    void _pasteNode();  // 粘贴
    void _cutNode();    // 剪切
    void _deleteNode(); // 删除
    eCommentItem *_addComment(const QPointF &pos);

  private:
    QGraphicsItemLayer *_commentLayer;
    QPointF _mousePos;
    QList<eCommentItem *> _commentList;
    QString _name;
  };

} // QtNodes
