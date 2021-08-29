#ifndef LIVEIMAGE_H
#define LIVEIMAGE_H

// Inserted from the answer in
// https://stackoverflow.com/questions/50567000/updating-an-image-from-c-to-qml

#include <QImage>
#include <QPainter>
#include <QQuickPaintedItem>

class LiveImage : public QQuickPaintedItem {
  Q_OBJECT
  Q_PROPERTY(QImage image MEMBER mImage WRITE SetImage)

  // Just storage for the image
  QImage mImage;

public:
  explicit LiveImage(QQuickItem *parent = nullptr);

  /*!
   * \brief setImage function to set the image in memory
   * \param image const QImage address
   */
  void SetImage(const QImage &image);

  /*!
   * \brief paint function to overwrite the paint call in QML
   * \param painter QPainter pointer to use and update
   */
  void paint(QPainter *painter) override;
};

#endif // LIVEIMAGE_H
