#include "imageprocessing.h"
#include <QFile>
#include <QImageReader>
#include <QImageWriter>
#include <chrono>
#include <iostream>
#include <thread>

ImageProcessing::ImageProcessing() {}

QImage ImageProcessing::sortImage(QString inputImagePath, int sortingAlg) {

  QFile input_path(inputImagePath);
  if (!input_path.exists()) {
    emit displayError("The input image doesn't exist");
    return QImage();
  }
  QImageReader reader(inputImagePath);

  std::shared_ptr<QImage> input_image = std::make_shared<QImage>(reader.read());
  if (input_image == nullptr) {
    return QImage();
  }

  QImage sorted_image;
  if (sortingAlg == BUBBLE_SORT) {
    sorted_image = bubble_sort(input_image, &intensity_compare);
  } else {
    emit displayError("Invalid sorting algorithm chosen");
  }

  return sorted_image;
}

QImage ImageProcessing::bubble_sort(std::shared_ptr<QImage> unsortedImage,
                                    bool (*metric)(QColor, QColor)) {

  const int max_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> thread_vector;

  int y_range = unsortedImage->height();

  for (int thread_num = 0; thread_num < max_threads; thread_num++) {
    int start = thread_num * y_range / max_threads;
    int end = (thread_num + 1) * y_range / max_threads;
    if (end > y_range) {
      end = y_range;
    }
    std::cout << "Start: " << start << "End: " << end << std::endl;
    std::thread th(bubble_sort_thread, unsortedImage, start, end, metric);
    thread_vector.push_back(std::move(th));
  }

  for (std::thread &th : thread_vector) {
    if (th.joinable()) {
      th.join();
    }
  }

  return *unsortedImage;
}

void ImageProcessing::bubble_sort_thread(std::shared_ptr<QImage> unsortedImage,
                                         int y_start, int y_end,
                                         bool (*metric)(QColor, QColor)) {
  int x_range = unsortedImage->width();
  for (int j = y_start; j < y_end; j++) {
    for (int z = 0; z < x_range; z++) {
      for (int i = 0; i < x_range - 1; i++) {
        QColor a = unsortedImage->pixelColor(i, j);
        QColor b = unsortedImage->pixelColor(i + 1, j);
        if (metric(a, b)) {
          unsortedImage->setPixelColor(i + 1, j, a);
          unsortedImage->setPixelColor(i, j, b);
        } else {
          continue;
        }
      }
    }
  }
}

bool ImageProcessing::intensity_compare(QColor a, QColor b) {
  return ((a.red() + a.green() + a.blue()) > (b.red() + b.green() + b.blue()));
}
