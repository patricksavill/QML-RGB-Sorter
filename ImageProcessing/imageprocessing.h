#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QImage>
#include <QString>
#include <future>

// We use a QObject class to allow for signal and slot connections
class ImageProcessing : public QObject {
  Q_OBJECT
public:
  ImageProcessing();

  /*!
   * \brief The SortAlgorithm enum is used by the front end to pass which
   * algorithm a user has selected to use
   */
  enum SortAlgorithm { BUBBLE_SORT, SELECTION_SORT };

  /*!
   * \brief SortImage Basic function to sort an image's pixels
   * \param inputImagePath Path to the image to sort
   * \param sortingAlg Integer corresponding to Enum of algorithms
   * Use as the switch to launch the sort as chosen by a user
   * \return QImage with sorted pixels
   */
  QImage SortImage(QString inputImagePath, int sortingAlg);

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
   * \brief BubbleSort Parent function to call bubble sort
   * \param unsortedImage Pointer to the unsorted QImage to sort
   * \param *metric Function pointer to the metric used for sorting
   * \return QImage, sorted
   */
  QImage BubbleSort(std::shared_ptr<QImage> unsortedImage,
                    bool (*metric)(QColor, QColor));

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
                               bool (*metric)(QColor, QColor));

  /*!
   * \brief SelectionSort Parent function to call the Selection sort threads
   * \param unsortedImage Pointer to the unsorted QImage to sort
   * \return
   */
  QImage SelectionSort(std::shared_ptr<QImage> unsortedImage,
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
   * \brief IntensityCompare Comparison function to compare intensity of
   * all channels combined evenly
   * \param a QColor to compare against b
   * \param b QColor to be compared against
   * \return True if a > b
   */
  static bool IntensityCompare(QColor a, QColor b);

  /*!
   * \brief IntensityCompare Overloaded comparison function to compare intensity
   * of all channels combined evenly
   * \param a QRgb to compare against b
   * \param b QRgb to be compared against
   * \return True if a > b
   * */
  static bool IntensityCompare(QRgb a, QRgb b);
};

#endif // IMAGEPROCESSING_H
