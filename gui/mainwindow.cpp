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
#include <QtCharts>

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

//    QLineSeries *series = new QLineSeries();
    QChart *chart = new QChart();
//    chart->legend()->hide();
//    chart->addSeries(series);
//    chart->createDefaultAxes();
    QChartView *chartView = new QChartView(/*chart*/);
    chartView->setRenderHint(QPainter::Antialiasing);

    timingLayout->addWidget(startSimulationButton);
    timingLayout->addWidget(chartView);
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

void MainWindow::openFile() {
    mFilePath =  QFileDialog::getOpenFileName(
                nullptr,
                "Open Document",
                QDir::currentPath(),
                "ocument files (*.v)");

    if(mFilePath.isNull() ) {
        throw std::runtime_error("File dont selected");
    }

    setEditor();
}

void MainWindow::startSimulation() {
    NetlistBuilder builder(mFilePath);
    builder.buildNetlist();
    auto netlist = builder.getNetlist();

    Simulation simulation(netlist);

    srand(static_cast<unsigned int>(time(nullptr)));

    auto inputNets = netlist->getPrimaryInputNets();
    QVector<QMap<QString, size_t>> primaryInputs {};
    primaryInputs.resize(5);
    for(int i = 0; i < 5; ++i) {
        // generate random primary inputs
        for(const auto& el: inputNets) {
            primaryInputs[i].insert(el->getName(), rand() % 2);
        }
    }
    qDebug()<<primaryInputs<<'\n';
    simulation.eventDrivenSimulation(primaryInputs);

    emit simulationOutput(simulation.getOutput());
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

