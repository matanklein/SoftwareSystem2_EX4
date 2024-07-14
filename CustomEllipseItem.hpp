/**
 * @author: matank214@gmail.com
 */
#pragma once

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPen>

/**
 * Component that help me display an ellipse with text inside when I hover on other items.
 */
class CustomEllipseItem : public QGraphicsEllipseItem {
   private:
    QString nodeData;
    QGraphicsTextItem* textItem = nullptr;
    QGraphicsRectItem* rectItem = nullptr;  // Rectangle around the text

   public:
    CustomEllipseItem(qreal x, qreal y, qreal w, qreal h, const QString& data, QGraphicsItem* parent = nullptr);

   protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;

    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
};