#include <QGuiApplication>
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

  // This is some interesting implementation to force an image update
  // LiveImage is a class that QML can instantiate to draw and image
  // ImageProvider is a class that we use to write new QImages too. In turn this
  // stored image is shown by the LiveImage object in QML allowing for live
  // updates of images and circumventing the need to use QUrls
  qmlRegisterType<LiveImage>("MyApp.Images", 1, 0, "LiveImage");
  engine.rootContext()->setContextProperty("LiveImageProvider",
                                           &FrontEndObject->mProvider);
  engine.rootContext()->setContextProperty("frontEndObject", FrontEndObject);
  engine.load(url);

  return app.exec();
}

void FrontEnd::errorPopup(QString errorMsg) {
  emit displayErrorPopup(errorMsg);
}

void FrontEnd::loadImage() {
  // TODO handle image loading logic and pass to back end, to then present to
  // front end
}

void FrontEnd::processImage() {
  // TODO implement the image processing
  QString result = "Received process request";
  ImageProcessing *image_processor = new ImageProcessing();
  connect(image_processor, &ImageProcessing::displayError, this,
          &FrontEnd::errorPopup);
  QImage sorted_image = image_processor->sortImage("../example-image.jpg");

  // TODO add in null check of the returned sorted image

  updateImage(sorted_image);
}

void FrontEnd::updateImage(QImage newImage) {

  // TODO use the passed in image, as currently it updates with a random solid
  // colour
  QImage image(100, 100, QImage::Format_ARGB32);
  image.fill(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
  this->mProvider.setImage(image);
}
