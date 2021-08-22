#ifndef LIVEIMAGE_H
#define LIVEIMAGE_H

// Inserted from the answer in
// https://stackoverflow.com/questions/50567000/updating-an-image-from-c-to-qml

#include <QImage>
#include <QPainter>
#include <QQuickPaintedItem>

class LiveImage : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(QImage image MEMBER m_image WRITE setImage)

  // Just storage for the image
  QImage m_image;

public:
  explicit LiveImage(QQuickItem *parent = nullptr);
  void setImage(const QImage &image);
  void paint(QPainter *painter) override;
};

#endif // LIVEIMAGE_H
