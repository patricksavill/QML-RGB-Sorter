#include "LiveImage.h"

LiveImage::LiveImage(QQuickItem *parent)
    : QQuickPaintedItem(parent), m_image{} {}

void LiveImage::paint(QPainter *painter) {
  QRectF bounding_rect = boundingRect();
  // TODO scale with preserved aspect ratio
  QImage scaled = m_image.scaled(bounding_rect.width(), bounding_rect.height());
  QPointF center = bounding_rect.center() - scaled.rect().center();

  if (center.x() < 0)
    center.setX(0);
  if (center.y() < 0)
    center.setY(0);
  painter->drawImage(center, scaled);
  //    painter->drawImage(0, 0, m_image);
}

void LiveImage::setImage(const QImage &image) {
  // Update the image
  m_image = image;

  // Redraw the image
  update();
}
