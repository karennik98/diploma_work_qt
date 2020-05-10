#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QObject>
#include <QString>

#include <memory>

class QTabBar;
class QTextEdit;

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
private:
    void setEditor();
private slots:
    void openFile();
private:
    std::shared_ptr<QTabBar> mTabBar;
    QString mFilePath;
    QTextEdit* mTextEdit;
};

#endif // MAINWINDOW_H
