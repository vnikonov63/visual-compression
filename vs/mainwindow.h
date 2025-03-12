#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <huffmantree.h>

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
    void paintEvent(QPaintEvent*);
    void SlotClickExport();
    void drawNode(QPainter& painter, Node* node, int x, int y, int xOffset, int yOffset, QString code);

private:
    Ui::MainWindow *ui;
    bool fileSet = false;
    HuffmanTree* ht;
};
#endif // MAINWINDOW_H
