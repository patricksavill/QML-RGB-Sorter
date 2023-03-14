#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QImage>
#include <QString>
#include <future>

#include "imageenums.h"

// We use a QObject class to allow for signal and slot connections
class ImageProcessing : public QObject {
  Q_OBJECT
public:
  ImageProcessing();

  /*!
   * \brief SortImage Basic function to sort an image's pixels
   * \param inputImagePath Path to the image to sort
   * \param sortingAlg Integer corresponding to Enum of algorithms
   * Use as the switch to launch the sort as chosen by a user
   * \param metricType Integer corresponding to Enum of pixel metric
   * \param dualAxisSort boolean flag to sort along x and y if true
   * \return QImage with sorted pixels
   */
  QImage SortImage(QString inputImagePath, int sortingAlg, int metricType,
                   bool dualAxisSort);

signals:
  /*!
   * \brief displayError Signal emitted whenever an error is encountered
   * \param errorMsg Error message to show in the front end
   */
  void displayError(QString errorMsg);

  /*!
   * \brief sortingTimeTaken Signal emitted after sort has taken place
   * \param sortingTime Double, time it took to sort
   */
  void sortingTimeTaken(double sortingTime);

private:
  /*!
   * \brief BubbleSortThread thread to perform bubble sort with
   * \param unsortedImage Shared pointer to unsorted image
   * \param y_start Vertical index to start on
   * \param y_end Vertical index to end on
   * \param *metric Function pointer to the metric used for sorting
   * \return None, sort is done in place on the shared pointer
   */
  static void BubbleSortThread(std::shared_ptr<QImage> unsortedImage,
                               int y_start, int y_end,
                               bool (*metric)(QRgb, QRgb));

  /*!
   * \brief InsertionSortThread thread to perform Insertion sort with
   * \param unsortedImage Shared pointer to unsorted image
   * \param y_start Vertical index to start on
   * \param y_end Vertical index to end on
   * \param *metric Function pointer to the metric used for sorting
   * \return None, sort is done in place on the shared pointer
   */
  static void InsertionSortThread(std::shared_ptr<QImage> unsortedImage,
                                  int y_start, int y_end,
                                  bool (*metric)(QRgb, QRgb));

  /*!
   * \brief SelectionSortThread thread to perform Selection sort with
   * \param unsortedImage Shared pointer to unsorted image
   * \param y_start Vertical index to start on
   * \param y_end Vertical index to end on
   * \param *metric Function pointer to the metric used for sorting
   * \return None, sort is done in place on the shared pointer
   */
  static void SelectionSortThread(std::shared_ptr<QImage> unsortedImage,
                                  int y_start, int y_end,
                                  bool (*metric)(QRgb, QRgb));

  /*!
   * \brief IntensityCompare Comparison function to compare intensity
   * of all channels combined evenly
   * \param a QRgb to compare against b
   * \param b QRgb to be compared against
   * \return True if a > b
   * */
  static bool IntensityCompare(QRgb a, QRgb b);

  /*!
   * \brief HueCompare Comparison function of the Hue in HSV
   * \param a QRgb to compare against b
   * \param b QRgb to be compared against
   * \return True if a > b
   */
  static bool HueCompare(QRgb a, QRgb b);
};

#endif // IMAGEPROCESSING_H
