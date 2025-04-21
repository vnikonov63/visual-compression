#include <QWidget>
#include <QPaintEvent>
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

private:
    HuffmanTree* ht_;
    void drawNode(QPainter& painter, Node* node, int x, int y, int xOffset, int yOffset);
};

#endif // HUFFMANTREEWIDGET_H
