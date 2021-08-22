#ifndef FRONTEND_H
#define FRONTEND_H

#include <QObject>

class FrontEnd : public QObject {
  Q_OBJECT
public:
  FrontEnd(QObject *parent = nullptr) {}

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
   * \brief processImage parent signal that should take in the image and sorting
   * metric then pass this onto the back end
   */
  void processImage();

signals:
  /*!
   * \brief displayErrorPopup Signal to show error on the front end
   * \param errorMsg QString of error message to display
   */
  void displayErrorPopup(QString errorMsg);
};

#endif // FRONTEND_H
