#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "frontend.h"

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

  engine.rootContext()->setContextProperty("frontEndObject", FrontEndObject);

  engine.load(url);

  return app.exec();
}

void FrontEnd::loadImage() {
  // TODO handle image loading logic and pass to back end, to then present to
  // front end
}

void FrontEnd::processImage() {
  // TODO implement the image processing
  QString result = "Received process request";
}
