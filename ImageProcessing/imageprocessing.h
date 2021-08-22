#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QString>
#include <thread>

// We use a QObject class to allow for signal and slot connections
class ImageProcessing : public QObject {
  Q_OBJECT
public:
  ImageProcessing();

  /*!
   * \brief sortImage Basic function to sort an image's pixels
   * \param inputImagePath Path to the image to sort
   * \return QImage with sorted pixels
   */
  QImage sortImage(QString inputImagePath);

signals:
  /*!
   * \brief displayError Signal emitted whenever an error is encountered
   * \param errorMsg Error message to show in the front end
   */
  void displayError(QString errorMsg);

private:
  std::shared_ptr<QImage> inputImage;
};

#endif // IMAGEPROCESSING_H
