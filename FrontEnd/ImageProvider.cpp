#include "ImageProvider.h"

ImageProvider::ImageProvider(QObject *parent)
    : QObject(parent)
{}

void ImageProvider::setImage(QImage const &image)
{
    m_image = image;
    emit imageChanged();
}

QImage ImageProvider::image() const
{
    return m_image;
}
