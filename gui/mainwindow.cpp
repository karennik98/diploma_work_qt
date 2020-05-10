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
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupTabBar();
}

MainWindow::~MainWindow() {

}

void MainWindow::setupTabBar() {
    QWidget *centralWidget = new QWidget(this);

    QScreen* screen = QApplication::screens().at(0);
    QSize screenSize = screen->availableSize();
    setFixedSize(QSize(screenSize.width()/2, screenSize.height()/2));

    mTabs = new QTabWidget(centralWidget);
    mTabs->setFixedSize(QSize(screenSize.width()/2, screenSize.height()/2));


    setupFileDialogTab();
    setupTextEditTab();
    setupTimingTab();
    setCentralWidget(centralWidget);
    show();
}

void MainWindow::setupTimingTab() {

    QWidget* timingAndSimulation = new QWidget(mTabs);
    QVBoxLayout* timingLayout = new QVBoxLayout(mTabs);
    QPushButton* startSimulationButton = new QPushButton("Strat simulation", timingAndSimulation);
    timingLayout->addWidget(startSimulationButton);
    timingAndSimulation->setLayout(timingLayout);

    mTabs->addTab(timingAndSimulation,"Timig diagram");
}

void MainWindow::setupTextEditTab() {
    mTextEdit = new QTextEdit(mTabs);

    mTabs->addTab(mTextEdit,"Editor");
}

void MainWindow::setupFileDialogTab() {
    QWidget* fileDialogWidget = new QWidget(mTabs);
    QPushButton* fileDialogButton = new QPushButton("open file", fileDialogWidget);

    QObject::connect(fileDialogButton, &QPushButton::pressed, this, &MainWindow::openFile);

    mTabs->addTab(fileDialogWidget, "Select file");
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

