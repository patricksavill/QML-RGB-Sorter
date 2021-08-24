#include "imageprocessing.h"
#include <QFile>
#include <QImageReader>
#include <QImageWriter>
#include <chrono>
#include <iostream>
#include <thread>

ImageProcessing::ImageProcessing() {}

QImage ImageProcessing::SortImage(QString inputImagePath, int sortingAlg) {

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
  auto start = std::chrono::high_resolution_clock::now();
  if (sortingAlg == BUBBLE_SORT) {
    sorted_image = BubbleSort(input_image, &IntensityCompare);
  } else if (sortingAlg == INSERTION_SORT) {
    sorted_image = InsertionSort(input_image, &IntensityCompare);
  } else {
    emit displayError("Invalid sorting algorithm chosen");
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_taken = end - start;
  emit sortingTimeTaken(time_taken.count());

  return sorted_image;
}

QImage ImageProcessing::BubbleSort(std::shared_ptr<QImage> unsortedImage,
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
    std::thread th(BubbleSortThread, unsortedImage, start, end, metric);
    thread_vector.push_back(std::move(th));
  }

  for (std::thread &th : thread_vector) {
    if (th.joinable()) {
      th.join();
    }
  }

  return *unsortedImage;
}

void ImageProcessing::BubbleSortThread(std::shared_ptr<QImage> unsortedImage,
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

QImage ImageProcessing::InsertionSort(std::shared_ptr<QImage> unsortedImage,
                                      bool (*metric)(QColor, QColor)) {
  // Still doing sorts per line, not globally, which means we an deploy threads
  //  const int max_threads = std::thread::hardware_concurrency();
  int max_threads = 1;
  std::vector<std::thread> thread_vector;

  int y_range = unsortedImage->height();

  for (int thread_num = 0; thread_num < max_threads; thread_num++) {
    int start = thread_num * y_range / max_threads;
    int end = (thread_num + 1) * y_range / max_threads;
    if (end > y_range) {
      end = y_range;
    }
    std::cout << "Start: " << start << "End: " << end << std::endl;
    std::thread th(InsertionSortThread, unsortedImage, start, end, metric);
    thread_vector.push_back(std::move(th));
  }

  for (std::thread &th : thread_vector) {
    if (th.joinable()) {
      th.join();
    }
  }
  //  InsertionSortThread(unsortedImage, 0, y_range, metric);

  return *unsortedImage;
}

void ImageProcessing::InsertionSortThread(std::shared_ptr<QImage> unsortedImage,
                                          int y_start, int y_end,
                                          bool (*metric)(QColor, QColor)) {
  int x_range = unsortedImage->width();
  int index = 0;
  QColor a, b;
  for (int j = y_start; j < y_end; j++) {
    for (int i = x_range - 1; i > -1; i--) {
      a = unsortedImage->pixelColor(i, j);
      index = i;
      // TODO need to pass in the metric for finding minimum as well as the
      // sorting metric or we implement both of them here
      for (int h = i - 1; h > -1; h--) {
        b = unsortedImage->pixelColor(h, j);
        if (metric(b, a)) {
          index = h;
        }
      }
      if (index != i) {
        unsortedImage->setPixelColor(index, j, a);
        unsortedImage->setPixelColor(i, j, b);
      }
    }
  }
}

bool ImageProcessing::IntensityCompare(QColor a, QColor b) {
  return ((a.red() + a.green() + a.blue()) > (b.red() + b.green() + b.blue()));
}
