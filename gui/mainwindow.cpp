#include "mainwindow.h"
#include <QTabBar>
#include <QApplication>
#include <QScreen>
#include <QTextEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QDebug>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupTabBar();
}

MainWindow::~MainWindow() {

}

void MainWindow::setupTabBar() {
    QWidget *centralWidget = new QWidget(this);
    QTabWidget *tabs = new QTabWidget(centralWidget);

    QScreen* screen = QApplication::screens().at(0);
    QSize screenSize = screen->availableSize();
    this->setFixedSize(QSize(screenSize.width()/2, screenSize.height()/2));

    tabs->setFixedSize(QSize(screenSize.width()/2, screenSize.height()/2));

    mTextEdit = new QTextEdit(tabs);
    mTextEdit->setStyleSheet({""});

    QWidget* fileDialogWidget = new QWidget(tabs);
    QPushButton* fileDialogButton = new QPushButton("open file", fileDialogWidget);

    QObject::connect(fileDialogButton, &QPushButton::pressed, this, &MainWindow::openFile);

    tabs->addTab(fileDialogWidget, "Select file");
    tabs->addTab(mTextEdit,"Editor");
    tabs->addTab(new QWidget(),"Timig diagram");

    setCentralWidget(centralWidget);
    show();
}

void MainWindow::setEditor() {
    std::shared_ptr<QFile> file = std::make_shared<QFile>();
    file->setFileName(mFilePath);
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream fileStream(&*file);

    QString line = fileStream.readLine();
    while(!line.isNull()) {
        mTextEdit->append(line);
        line = fileStream.readLine();
    }
}

void MainWindow::openFile() {
    mFilePath =  QFileDialog::getOpenFileName(
                nullptr,
                "Open Document",
                QDir::currentPath(),
                "All files (*.*) ;; Document files (*.doc *.rtf *.v);; PNG files (*.png)");

    if(mFilePath.isNull() ) {
        throw std::runtime_error("File dont selected");
    }

    setEditor();
}
