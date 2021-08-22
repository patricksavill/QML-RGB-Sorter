#ifndef FRONTEND_H
#define FRONTEND_H

#include <QObject>

class FrontEnd : public QObject {
  Q_OBJECT
public:
  FrontEnd(QObject *parent = nullptr) {}

public slots:
  /*!
   * \brief loadImage Called when a user is to load in a new image
   */
  void loadImage();

  /*!
   * \brief processImage parent signal that should take in the image and sorting
   * metric then pass this onto the back end
   */
  void processImage();
};

#endif // FRONTEND_H
