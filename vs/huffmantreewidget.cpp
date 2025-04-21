#include <QSize>
#include <QPainter>
#include <QPaintEvent>

#include "huffmantreewidget.h"

HuffmanTreeWidget::HuffmanTreeWidget(QWidget* parent)
    : QWidget(parent), ht_(nullptr) {}

void HuffmanTreeWidget::setTree(HuffmanTree* ht) {
    ht_ = ht;

    if (ht_ != nullptr) {
        QSize dimensions = ht_->ComputeScreenDimensions();
        setMinimumSize(dimensions.width() * 40 , dimensions.height() * 100);
    }

    update();
}

void HuffmanTreeWidget::paintEvent(QPaintEvent*) {
    if (ht_ == nullptr || ht_->GetRoot() == nullptr) {
        return;
    }

    QPainter painter(this);
    drawNode(painter, ht_->GetRoot(), width()/2, 50, width()/4, 100);
}

void HuffmanTreeWidget::drawNode(QPainter& painter, Node* node, int x, int y, int xOffset, int yOffset) {
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
        QRect textRect(x - radius / 2, y, radius, radius);
        drawNode(painter, node->left_, childX, childY, xOffset / 2, yOffset);
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
        drawNode(painter, node->right_, childX, childY, xOffset / 2, yOffset);
    }
}
