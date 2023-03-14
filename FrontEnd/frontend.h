#ifndef FRONTEND_H
#define FRONTEND_H

#include "ImageProvider.h"
#include <QImage>
#include <QObject>

class FrontEnd : public QObject {
  Q_OBJECT
public:
  FrontEnd(QObject *parent = nullptr) {}
  ImageProvider mLoadedProvider{};
  ImageProvider mSortedProvider{};

public slots:

  /*!
   * \brief errorPopup Slot to accept errors raised and then signal to the front
   * end with displayErrorPopup
   * \param errorMsg QString of error message to display
   */
  void errorPopup(QString errorMsg);

  /*!
   * \brief loadImage Called when a user is to load in a new image
   * \param filePath QString file path passed in from QML
   */
  void loadImage(QString filePath);

  /*!
   * \brief processImage parent slot that should take in the image and sorting
   * metric then pass this onto the back end
   * \param sortType enum, sorting algorithm chosen passed in from QML
   * \param metricType enum, pixel comparison metric chosen in QML
   * \param dualAxisSort boolean, flag if the image will be sorted twice (x and
   * y) or just along x
   */
  void processImage(int sortType, int metricType, bool dualAxisSort);

  /*!
   * \brief updateImage Slot to push a new QImage to and refresh the UI with
   * \param newImage    QImage to show in the UI
   * \param provider    Pointer to Image Provider to use. Typically
   * mSortedProvider or mLoadedProvider
   */
  void updateImage(QImage newImage, ImageProvider *provider);

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

  /*!
   * \brief imageLoaded Signal to QML indicating image load was successful
   */
  void imageLoaded();

private:
  QString mSourceImagePath;
};

#endif // FRONTEND_H
