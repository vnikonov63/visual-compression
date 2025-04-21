#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

#include <huffmantree.h>
#include <huffmantreewidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SlotClickExport();

private:
    Ui::MainWindow *ui;
    bool fileSet = false;
    HuffmanTree* ht_;
    HuffmanTreeWidget* htw_;
    QScrollArea* scrollArea_;

};
#endif // MAINWINDOW_H
