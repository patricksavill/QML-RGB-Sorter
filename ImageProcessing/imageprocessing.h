#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QString>
#include <future>
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
  /*!
   * \brief bubble_sort An implementation of bubble sort
   * \param unsortedImage The unsorted QImage to sort
   * \return QImage, sorted
   */
  QImage bubble_sort(std::shared_ptr<QImage> unsortedImage);

  /*!
   * \brief bubble_sort_thread thread to perform bubble sort with
   * \param unsortedImage Shared pointer to unsorted image
   * \param y_start Vertical index to start on
   * \param y_end Vertical index to end on
   */
  static void bubble_sort_thread(std::shared_ptr<QImage> unsortedImage,
                                 int y_start, int y_end);

  /*!
   * \brief intensity_compare Comparison function to compare intensity of all
   * channels combined
   * \param a QColor to compare against b
   * \param b QColor to be compared against
   * \return True if a > b
   */
  static bool intensity_compare(QColor a, QColor b);
};

#endif // IMAGEPROCESSING_H
