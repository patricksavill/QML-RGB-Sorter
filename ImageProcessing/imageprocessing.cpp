#include "imageprocessing.h"

ImageProcessing::ImageProcessing() {}

QImage ImageProcessing::sortImage(QString inputImagePath) {

  QFile inputPath(inputImagePath);
  if (!inputPath.exists()) {
    emit displayError("The input image doesn't exist");
    return QImage();
  }
  QImageReader reader(inputImagePath);

  return QImage();
}
