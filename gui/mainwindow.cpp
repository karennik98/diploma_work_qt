#include "mainwindow.h"
#include "netlist_builder/netlistbuilder.h"
#include "simulation/simulation.h"
#include "db/netlist.h"

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
    setupSimulationTab();
    setCentralWidget(centralWidget);
    show();
}

void MainWindow::setupSimulationTab() {

    QWidget* timingAndSimulation = new QWidget(mTabs);
    QVBoxLayout* timingLayout = new QVBoxLayout(mTabs);

    QPushButton* startSimulationButton = new QPushButton("Strat simulation", timingAndSimulation);
    QObject::connect(startSimulationButton, &QPushButton::pressed, this, &MainWindow::startSimulation);

    mSimulationOutputTextEdit = new QTextEdit(mTabs);
    QObject::connect(this, &MainWindow::simulationOutput, this, &MainWindow::dumpSimulationOutput);


    mChartView = new QChartView();

    mChartView->setRenderHint(QPainter::Antialiasing);

    timingLayout->addWidget(startSimulationButton);
    timingLayout->addWidget(mChartView);
    timingLayout->addWidget(mSimulationOutputTextEdit);
    timingAndSimulation->setLayout(timingLayout);

    mTabs->addTab(timingAndSimulation,"Simulation");
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

void MainWindow::setupChartValues() {
    QChart *chart = new QChart();
    size_t distance = 2;
    auto data = mSimulation->getDumpedData();
    qDebug()<<data;
    for(auto el = data.begin(); el != data.end(); ++el) {
        QLineSeries* series = new QLineSeries();
        auto inputVector = el.value();
        for(int i = 0; i < inputVector.size(); ++i) {
            if(i == 0 && inputVector[i] == 0) {
                series->append(i, inputVector[i] + distance);
            } else if(i == 0 && inputVector[i] == 1) {
                series->append(i, inputVector[i] + distance);
            } else if((inputVector[i] != inputVector[i - 1]) && inputVector[i] == 1) {
                series->append(i, inputVector[i - 1] + distance);
                series->append(i, inputVector[i] + distance);
            } else if((inputVector[i] != inputVector[i - 1]) && inputVector[i] == 0) {
                series->append(i, inputVector[i - 1] + distance);
                series->append(i, inputVector[i] + distance);
            } else if(inputVector[i] == 1) {
                series->append(i, inputVector[i] + distance);
            } else {
                series->append(i, inputVector[i] + distance);
            }
        }
        distance += 2;
        chart->addSeries(series);
    }

    chart->legend()->hide();
//    chart->addSeries(series);
    chart->createDefaultAxes();
    mChartView->setChart(chart);
}

void MainWindow::openFile() {
    mFilePath =  QFileDialog::getOpenFileName(
                mTabs,
                ":/verilog_files",
                QDir::currentPath(),
                "Document files (*.v)");

    if(mFilePath.isNull() ) {
        throw std::runtime_error("File dont selected");
    }

    setEditor();
}

void MainWindow::startSimulation() {

    NetlistBuilder builder(mFilePath);
    builder.buildNetlist();
    auto netlist = builder.getNetlist();

    mSimulation = std::make_shared<Simulation>(netlist);

    srand(static_cast<unsigned int>(time(nullptr)));

    auto inputNets = netlist->getPrimaryInputNets();
    QVector<QMap<QString, size_t>> primaryInputs {};
    primaryInputs.resize(10);
    for(int i = 0; i < 10; ++i) {
        // generate random primary inputs
        for(const auto& el: inputNets) {
            primaryInputs[i].insert(el->getName(), rand() % 2);
        }
    }
    qDebug()<<primaryInputs<<'\n';
    mSimulation->eventDrivenSimulation(primaryInputs);

    emit simulationOutput(mSimulation->getOutput());
    setupChartValues();
}

void MainWindow::dumpSimulationOutput(std::shared_ptr<QStringList> output) {
    mSimulationOutputTextEdit->clear();
    for(auto str : *output) {
        mSimulationOutputTextEdit->append(str);
    }
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

