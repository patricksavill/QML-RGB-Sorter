#ifndef FRONTEND_H
#define FRONTEND_H

#include "ImageProvider.h"
#include <QImage>
#include <QObject>

class FrontEnd : public QObject {
  Q_OBJECT
public:
  FrontEnd(QObject *parent = nullptr) {}
  ImageProvider mProvider{};

public slots:

  /*!
   * \brief errorPopup Slot to accept errors raised and then signal to the front
   * end with displayErrorPopup
   * \param errorMsg QString of error message to display
   */
  void errorPopup(QString errorMsg);

  /*!
   * \brief loadImage Called when a user is to load in a new image
   */
  void loadImage();

  /*!
   * \brief processImage parent slot that should take in the image and sorting
   * metric then pass this onto the back end
   */
  void processImage();

  /*!
   * \brief updateImage Slot to push a new QImage to and refresh the UI with
   * \param newImage    QImage to show in the UI
   */
  void updateImage(QImage newImage);

  /*!
   * \brief updateSortTime Slot to update the sorting time in the front end
   * \param sortingTime Double, duration to display
   */
  void updateSortTime(double sortingTime);

signals:
  /*!
   * \brief displayErrorPopup Signal to show error on the front end
   * \param errorMsg QString of error message to display
   */
  void displayErrorPopup(QString errorMsg);

  /*!
   * \brief displaySortingTime Signal to show the sorting time
   * \param sortingText QString of sorting text to show
   */
  void displaySortingTime(QString sortingText);
};

#endif // FRONTEND_H
