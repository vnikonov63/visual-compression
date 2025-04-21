#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QFile>
#include <QScrollArea>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), ht_(nullptr) {
    ui->setupUi(this);

    htw_ = new HuffmanTreeWidget();

    scrollArea_ = new QScrollArea();
    scrollArea_->setWidgetResizable(true);
    scrollArea_->setWidget(htw_);

    setCentralWidget(scrollArea_);

    connect(ui->actionUpload_File, &QAction::triggered, this, &MainWindow::SlotClickExport);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ht_;
}

void MainWindow::SlotClickExport() {
    QDir dir(QDir::currentPath());
    for (int i = 0; i < 6; i += 1) {
        dir.cdUp();
    }
    QString parentAbsolutePath = dir.absolutePath();

    QString fileName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Open a file"), parentAbsolutePath, "*.txt");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    fileSet = true;

    if (ht_) {
        delete ht_;
        ht_ = nullptr;
    }

    ht_ = new HuffmanTree(file);
    htw_->setTree(ht_);
}
