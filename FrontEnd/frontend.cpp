#include <QGuiApplication>
#include <QImageReader>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

#include "ImageProvider.h"
#include "LiveImage.h"
#include "frontend.h"
#include "imageprocessing.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  FrontEnd *FrontEndObject = new FrontEnd(&app);

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);

  /*
   * This is some interesting implementation to force an image update
   * LiveImage is a class that QML can instantiate to draw and image
   * ImageProvider is a class that we use to write new QImages too. In turn this
   * stored image is shown by the LiveImage object in QML allowing for live
   * updates of images and circumventing the need to use QUrls
   */

  qmlRegisterType<LiveImage>("QMLLiveImage.Images", 1, 0, "LiveImage");

  // Here we register the enums for use in the front end connection to back end
  qmlRegisterType<ImageSortEnum>("ImageSort", 1, 0, "ImageSortEnum");

  // We use LoadedImageProvider for the initial image, and SortedImageProvider
  // for the sorted image
  engine.rootContext()->setContextProperty("LoadedImageProvider",
                                           &FrontEndObject->mLoadedProvider);
  engine.rootContext()->setContextProperty("SortedImageProvider",
                                           &FrontEndObject->mSortedProvider);
  engine.rootContext()->setContextProperty("frontEndObject", FrontEndObject);
  engine.load(url);

  return app.exec();
}

void FrontEnd::errorPopup(QString errorMsg) {
  emit displayErrorPopup(errorMsg);
}

void FrontEnd::loadImage(QString filePath) {
  QString local_path =
      filePath.remove(0, 6); // Path from QML starts with file://
  if (!QFile::exists(local_path)) {
    emit displayErrorPopup(QString("Could not find file: %0").arg(local_path));
  }

  QImageReader reader(local_path);
  QImage new_image = reader.read();
  if (new_image.isNull()) {
    emit displayErrorPopup("Couldn't read an image");
    return;
  }

  // Image loaded, update the loaded provider and source image path for use
  // later
  mSourceImagePath = local_path;
  updateImage(new_image, &this->mLoadedProvider);
}

void FrontEnd::processImage(int sortType, int metricType, bool dualAxisSort) {

  if (mSourceImagePath.isNull()) {
    emit displayErrorPopup("No image loaded, cannot sort");
    return;
  }

  ImageProcessing *image_processor = new ImageProcessing();
  connect(image_processor, &ImageProcessing::displayError, this,
          &FrontEnd::errorPopup);
  connect(image_processor, &ImageProcessing::sortingTimeTaken, this,
          &FrontEnd::updateSortTime);

  QImage sorted_image;

  // Safety check the passed sorting alg is implemented
  if (sortType == ImageSortEnum::BUBBLE_SORT ||
      sortType == ImageSortEnum::INSERTION_SORT ||
      sortType == ImageSortEnum::SELECTION_SORT) {
    sorted_image = image_processor->SortImage(mSourceImagePath, sortType,
                                              metricType, dualAxisSort);
  } else {
    emit displayErrorPopup(
        QString("Unknown sort type selected: %0").arg(sortType));
    return;
  }

  if (sorted_image.isNull()) {
    return;
  }

  updateImage(sorted_image, &this->mSortedProvider);
}

void FrontEnd::updateImage(QImage newImage, ImageProvider *provider) {

  provider->SetImage(newImage);
}

void FrontEnd::updateSortTime(double sortingTime) {
  emit displaySortingTime(
      QString("Sorting took: %0 s").arg(sortingTime, 0, 'g', 3));
}
