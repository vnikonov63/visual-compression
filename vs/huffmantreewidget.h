#include <QWidget>
#include <QRect>
#include <QString>
#include <QVector>
#include <QPaintEvent>
#include <QMouseEvent>
#include "huffmantree.h"

#ifndef HUFFMANTREEWIDGET_H
#define HUFFMANTREEWIDGET_H

class HuffmanTreeWidget : public QWidget {
    Q_OBJECT
public:
    explicit HuffmanTreeWidget(QWidget* parent = nullptr);
    void setTree(HuffmanTree* ht);
protected:
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* ev) override;

private:
    HuffmanTree* ht_;
    void drawNode(QPainter& painter, Node* node, int x, int y, int xOffset, int yOffset, QString seq);

    struct InfoRegion {
        QRect rect;
        QString text;
    };
    QVector<InfoRegion> info_regions_;
};

#endif // HUFFMANTREEWIDGET_H
