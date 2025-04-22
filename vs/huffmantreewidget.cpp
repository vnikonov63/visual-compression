#include <QSize>
#include <QPainter>
#include <QPoint>
#include <QPaintEvent>
#include <QToolTip>

#include "huffmantreewidget.h"

HuffmanTreeWidget::HuffmanTreeWidget(QWidget* parent)
    : QWidget(parent), ht_(nullptr) {
    setMouseTracking(true);

    QFont fontt = QToolTip::font();
    fontt.setPointSize(12);
    QToolTip::setFont(fontt);
}

void HuffmanTreeWidget::setTree(HuffmanTree* ht) {
    ht_ = ht;

    if (ht_ != nullptr) {
        QSize dimensions = ht_->ComputeScreenDimensions();
        setMinimumSize(dimensions.width() * 40 , dimensions.height() * 100);
    }

    update();
}

void HuffmanTreeWidget::paintEvent(QPaintEvent*) {
    info_regions_.clear();
    if (ht_ == nullptr || ht_->GetRoot() == nullptr) {
        return;
    }

    QPainter painter(this);
    drawNode(painter, ht_->GetRoot(), width()/2, 50, width()/4, 100, "");
}

void HuffmanTreeWidget::drawNode(QPainter& painter, Node* node, int x, int y, int xOffset, int yOffset, QString seq) {
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

    if (!node->isDummy_) {
        info_regions_.append({textRect, seq});
    }

    if (node->left_) {
        int childX = x - xOffset;
        int childY = y + yOffset;
        QPen pen(Qt::black);
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(x, y, childX, childY);
        drawNode(painter, node->left_, childX, childY, xOffset / 2, yOffset, seq + "0");
    }

    if (node->right_) {
        int childX = x + xOffset;
        int childY = y + yOffset;
        QPen pen(Qt::black);
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(x, y, childX, childY);
        drawNode(painter, node->right_, childX, childY, xOffset / 2, yOffset, seq + "1");
    }
}

void HuffmanTreeWidget::mouseMoveEvent(QMouseEvent* ev) {
    bool insideRect = false;

    for (const auto& region : info_regions_) {
        if (region.rect.contains(ev->pos()) ) {
            QPoint globalTip = mapToGlobal(region.rect.center() + QPoint(0,20));
            QToolTip::showText(globalTip, region.text, this);
            insideRect = true;
            break;
        }
    }

    if (!insideRect) {
        QToolTip::hideText();
    }
}
