#ifndef IMAGE_ENUMS_H
#define IMAGE_ENUMS_H

#include <QObject>

/*!
 * \brief The ImageSortEnum class contains the sorting enums to register in the
 * front end, and then control the backend enumerations that are used in QML.
 *
 * Required derivation from QObject to use with QML, can't just declare an enum
 */
class ImageSortEnum : public QObject {
  Q_OBJECT

public:
  // Default constructor, required for classes you expose to QML.
  ImageSortEnum() : QObject() {}

  /*!
   * \brief The SortAlgorithm enum is used by the front end to pass which
   * algorithm a user has selected to use
   */
  enum SortAlgorithm { NONE = 0, BUBBLE_SORT, INSERTION_SORT, SELECTION_SORT };
  Q_ENUM(SortAlgorithm) // Declared so QML can use the enums

  /*!
   * \brief The PixelMetric enum used by front end for the user to choose the
   * metric that the back end should use for pixel comparisons
   */
  enum PixelMetric { RGB_INTENSITY, HUE };
  Q_ENUM(PixelMetric)
};

#endif
