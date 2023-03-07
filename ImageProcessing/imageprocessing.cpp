#include "imageprocessing.h"
#include <QFile>
#include <QImageReader>
#include <QImageWriter>
#include <chrono>
#include <iostream>
#include <thread>

ImageProcessing::ImageProcessing() {}

QImage ImageProcessing::SortImage(QString inputImagePath, int sortingAlg,
                                  bool dualAxisSort) {

  QFile input_path(inputImagePath);
  if (!input_path.exists()) {
    emit displayError(
        QString("The input image doesn't exist: %0").arg(inputImagePath));
    return QImage();
  }
  QImageReader reader(inputImagePath);

  std::shared_ptr<QImage> input_image = std::make_shared<QImage>(reader.read());
  if (input_image == nullptr) {
    emit displayError("Couldn't read in image");
    return QImage();
  }

  // Determine pixel metric function to use
  bool (*pixel_metric)(QRgb, QRgb);
  QImage sorted_image;
  auto start = std::chrono::high_resolution_clock::now();
  if (sortingAlg == ImageSortEnum::BUBBLE_SORT) {
    sorted_image = BubbleSort(input_image, &IntensityCompare, dualAxisSort);
  } else if (sortingAlg == ImageSortEnum::INSERTION_SORT) {
    sorted_image = InsertionSort(input_image, pixel_metric, dualAxisSort);
  } else if (sortingAlg == ImageSortEnum::SELECTION_SORT) {
    sorted_image = SelectionSort(input_image, pixel_metric, dualAxisSort);
  } else {
    emit displayError("Invalid sorting algorithm chosen");
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time_taken = end - start;
  emit sortingTimeTaken(time_taken.count());

  return sorted_image;
}

QImage ImageProcessing::BubbleSort(std::shared_ptr<QImage> unsortedImage,
                                   bool (*metric)(QColor, QColor),
                                   bool dualAxisSort) {
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

  if (dualAxisSort) {
    // Attempt the transpose, sort again, then return the original image.
    QImage x1 = unsortedImage->transformed(QMatrix().rotate(90.0));
    unsortedImage->swap(x1);

    y_range = unsortedImage->height();

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

    // Swap the data back, rotated correctly, and return
    QImage x2 = unsortedImage->transformed(QMatrix().rotate(-90.0));
    unsortedImage->swap(x2);
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
                                      bool (*metric)(QRgb, QRgb),
                                      bool dualAxisSort) {

  // TODO all these parent functions are pretty much the same, could abstract
  // into one parent function

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
    std::thread th(InsertionSortThread, unsortedImage, start, end, metric);
    thread_vector.push_back(std::move(th));
  }

  for (std::thread &th : thread_vector) {
    if (th.joinable()) {
      th.join();
    }
  }

  if (dualAxisSort) {
    // Attempt the transpose, sort again, then return the original image.
    QImage x1 = unsortedImage->transformed(QMatrix().rotate(90.0));
    unsortedImage->swap(x1);

    y_range = unsortedImage->height();

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

    // Swap the data back, rotated correctly, and return
    QImage x2 = unsortedImage->transformed(QMatrix().rotate(-90.0));
    unsortedImage->swap(x2);
  }

  return *unsortedImage;
}

void ImageProcessing::InsertionSortThread(std::shared_ptr<QImage> unsortedImage,
                                          int y_start, int y_end,
                                          bool (*metric)(QRgb, QRgb)) {
  int x_range = unsortedImage->width();
  QRgb *scan_line;
  for (int j = y_start; j < y_end; j++) {
    scan_line = (QRgb *)unsortedImage->scanLine(j);
    for (int i = 1; i < x_range - 1; i++) {

      QRgb temp = scan_line[i];

      int t = i - 1;
      while (t >= 0 && metric(scan_line[t], temp)) {
        // Move pixels along that are bigger than temp
        scan_line[t + 1] = scan_line[t];
        t -= 1;
      }
      // Put temp into place, lower than all it compared to
      scan_line[t + 1] = temp;
    }
  }
}

QImage ImageProcessing::SelectionSort(std::shared_ptr<QImage> unsortedImage,
                                      bool (*metric)(QRgb, QRgb),
                                      bool dualAxisSort) {
  // Still doing sorts per line, not globally, which means we an deploy threads
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
    std::thread th(SelectionSortThread, unsortedImage, start, end, metric);
    thread_vector.push_back(std::move(th));
  }

  for (std::thread &th : thread_vector) {
    if (th.joinable()) {
      th.join();
    }
  }

  if (dualAxisSort) {
    // Attempt the transpose, sort again, then return the original image.
    QImage x1 = unsortedImage->transformed(QMatrix().rotate(90.0));
    unsortedImage->swap(x1);

    y_range = unsortedImage->height();

    for (int thread_num = 0; thread_num < max_threads; thread_num++) {
      int start = thread_num * y_range / max_threads;
      int end = (thread_num + 1) * y_range / max_threads;
      if (end > y_range) {
        end = y_range;
      }
      std::cout << "Start: " << start << "End: " << end << std::endl;
      std::thread th(SelectionSortThread, unsortedImage, start, end, metric);
      thread_vector.push_back(std::move(th));
    }

    for (std::thread &th : thread_vector) {
      if (th.joinable()) {
        th.join();
      }
    }

    // Swap the data back, rotated correctly, and return
    QImage x2 = unsortedImage->transformed(QMatrix().rotate(-90.0));
    unsortedImage->swap(x2);
  }

  return *unsortedImage;
}

void ImageProcessing::SelectionSortThread(std::shared_ptr<QImage> unsortedImage,
                                          int y_start, int y_end,
                                          bool (*metric)(QRgb, QRgb)) {
  int x_range = unsortedImage->width();
  int index = 0;
  QRgb *scan_line;
  for (int j = y_start; j < y_end; j++) {
    scan_line = (QRgb *)unsortedImage->scanLine(j);
    for (int i = 0; i < x_range; i++) {
      index = i;
      for (int h = i + 1; h < x_range; h++) {
        if (metric(scan_line[index], scan_line[h])) {
          index = h;
        }
      }
      if (index != i) {
        QRgb temp = scan_line[i];
        scan_line[i] = scan_line[index];
        scan_line[index] = temp;
      }
    }
  }
}

bool ImageProcessing::IntensityCompare(QColor a, QColor b) {
  return ((a.red() + a.green() + a.blue()) > (b.red() + b.green() + b.blue()));
}

bool ImageProcessing::IntensityCompare(QRgb a, QRgb b) {
  return ((qRed(a) + qGreen(a) + qBlue(a)) > (qRed(b) + qGreen(b) + qBlue(b)));
}
