#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

// Inserted from the answer in
// https://stackoverflow.com/questions/50567000/updating-an-image-from-c-to-qml

#include <QImage>
#include <QObject>

class ImageProvider : public QObject {
  Q_OBJECT
  Q_PROPERTY(QImage image MEMBER mImage READ ProvideImage WRITE SetImage NOTIFY
                 imageChanged)

  QImage mImage;

public:
  explicit ImageProvider(QObject *parent = nullptr);

  /*!
   * \brief SetImage function to update the QImage held by the class
   * \param image const address to the QImage to use
   */
  void SetImage(QImage const &image);

  /*!
   * \brief ProvideImage functino to return the QImage held, when read from
   * \return QImage
   */
  QImage ProvideImage() const;

signals:
  /*!
   * \brief imageChanged Signal to send out once the held QImage is updated
   */
  void imageChanged();
};

#endif // IMAGEPROVIDER_H
