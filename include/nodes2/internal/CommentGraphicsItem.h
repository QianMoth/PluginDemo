/**
 * @file CommentGraphicsItem.h
 * @author moth (QianMoth@qq.com)
 * @brief 注释文本框
 * @version 0.1
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <QGraphicsTextItem>

#include "Types.h"
#include "Export.hpp"

namespace QtNodes
{

#define TYPE_ID_COMMENT 0xFFFF + 1701

  //-----------------------------------------------------------------------------------------
  //! eCommentItem
  //! A comment graphics item.
  //-----------------------------------------------------------------------------------------
  class eCommentItem : public QGraphicsTextItem
  {
    Q_OBJECT
  public:
    eCommentItem(QGraphicsItem *parent);

    enum
    {
      Type = TYPE_ID_COMMENT
    };
    int type() const { return Type; }
    int _getTextLength() { return m_realText.length(); }
    bool isEdited() { return m_edited; }

    // void saveToXml(QDomElement &node) const;
    // void loadFromXml(const QDomElement &node);
    QJsonObject save() const;
    void restore(QJsonObject const &json);

  protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *me);
    void mousePressEvent(QGraphicsSceneMouseEvent *me);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *me);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *me);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *me);
    void focusOutEvent(QFocusEvent *event);
    QPainterPath shape() const;
    QRectF boundingRect() const;

  private Q_SLOTS:
    void _onUpdateSize(const QSizeF newSize);

  private:
    void _formatOutput();
    void _init();

  private:
    static const int RESIZE_AREA = 10; // default resize area from bottom-right border (in pixels)
    QString m_realText;                // store real text
    int m_mode;                        // text or html mode
    QColor m_colorBack;                // background color
    QColor m_colorText;                // text color
    bool m_isResizing;                 // is resizing
    bool m_edited;                     // is editing
    QPointF m_mouseDownPos;            // mouse pos
    qreal m_width;                     // widget width
    qreal m_height;                    // widget height
  };

} // QtNodes
