#include "LiveImage.h"

LiveImage::LiveImage(QQuickItem *parent)
    : QQuickPaintedItem(parent), mImage{} {}

void LiveImage::paint(QPainter *painter) {
  QRectF bounding_rect = boundingRect();

  if (mImage.isNull()) {
    return;
  }

  QImage scaled = mImage.scaled(bounding_rect.width(), bounding_rect.height(),
                                Qt::KeepAspectRatio);
  QPointF center = bounding_rect.center() - scaled.rect().center();

  if (center.x() < 0)
    center.setX(0);
  if (center.y() < 0)
    center.setY(0);
  painter->drawImage(center, scaled);
}

void LiveImage::SetImage(const QImage &image) {
  // Update the image
  mImage = image;

  // Redraw the image
  update();
}
