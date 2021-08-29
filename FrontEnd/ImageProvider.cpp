#include "ImageProvider.h"

ImageProvider::ImageProvider(QObject *parent) : QObject(parent) {}

void ImageProvider::SetImage(QImage const &image) {
  mImage = image;
  emit imageChanged();
}

QImage ImageProvider::ProvideImage() const { return mImage; }
