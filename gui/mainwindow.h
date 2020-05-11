#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QObject>
#include <QString>
#include <QTextStream>

#include <memory>

class QTabBar;
class QTextEdit;
class QTabWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    void setupTabBar();
    void setupSimulationTab();
    void setupTextEditTab();
    void setupFileDialogTab();
private:
    void setEditor();
private slots:
    void openFile();
    void startSimulation();
    void dumpSimulationOutput(std::shared_ptr<QStringList> output);
signals:
    void simulationOutput(std::shared_ptr<QStringList> output);
private:
    std::shared_ptr<QTabBar> mTabBar;
    QString mFilePath;
    QTextEdit* mTextEdit;
    QTextEdit* mSimulationOutputTextEdit;
    QTabWidget* mTabs;
};

#endif // MAINWINDOW_H
