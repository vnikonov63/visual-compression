#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QFile>
#include <QScrollArea>
#include <QPainter>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    ht(nullptr)
{
    this->setFixedSize(1600, 1000);
    ui->setupUi(this);
    connect(ui->actionUpload_File, &QAction::triggered, this, &MainWindow::SlotClickExport);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ht;
}

void MainWindow::paintEvent(QPaintEvent*) {
    if (!fileSet || ht == nullptr) {
        return;
    }

    QPainter painter(this);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::black);

    int startX = width() / 2;
    int startY = 50;

    drawNode(painter, ht->GetRoot(), startX, startY, 400, 100, "");
}

void MainWindow::drawNode(QPainter& painter, Node* node, int x, int y, int xOffset, int yOffset, QString code) {
    if (node == nullptr) return;

    int radius = 40;

    QString text;
    if (node->isDummy_) {
        QPen pen(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
        text = QString::number(node->freq_);
    } else {
        QPen pen(Qt::blue);
        pen.setWidth(3);
        painter.setPen(pen);
        text = QString("'%1'\n%2").arg(node->ch_).arg(node->freq_);
    }

    QRect textRect(x - radius / 2, y, radius, radius);
    painter.drawText(textRect, Qt::AlignCenter, text);

    if (node->left_) {
        int childX = x - xOffset;
        int childY = y + yOffset;
        QPen pen(Qt::black);
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(x, y, childX, childY);
        int midX = (x + childX) / 2;
        int midY = (y + childY) / 2;
        painter.drawText(midX, midY, code + "0");
        QRect textRect(x - radius / 2, y, radius, radius);
        drawNode(painter, node->left_, childX, childY, xOffset / 2, yOffset, code + "0");
    }

    if (node->right_) {
        int childX = x + xOffset;
        int childY = y + yOffset;
        QPen pen(Qt::black);
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(x, y, childX, childY);
        int midX = (x + childX) / 2;
        int midY = (y + childY) / 2;
        painter.drawText(midX, midY, code + "1");
        drawNode(painter, node->right_, childX, childY, xOffset / 2, yOffset, code + "1");
    }
}

void MainWindow::SlotClickExport() {
    QDir dir(QDir::currentPath());
    for (int i = 0; i < 6; i += 1) {
        dir.cdUp();
    }
    QString parentAbsolutePath = dir.absolutePath();

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    QString::fromUtf8("Open a file"),
                                                    parentAbsolutePath,
                                                    "*.txt");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    fileSet = true;

    if (ht) {
        delete ht;
        ht = nullptr;
    }

    ht = new HuffmanTree(file);
    update();
}
