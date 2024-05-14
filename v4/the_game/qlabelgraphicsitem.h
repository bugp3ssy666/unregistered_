#ifndef QLABELGRAPHICSITEM_H
#define QLABELGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QLabel>
#include <QFont>

class QLabelGraphicsItem: public QGraphicsItem
{
public:
    QLabelGraphicsItem(QWidget *parent = nullptr){
        label = new QLabel(parent);
        // painter = new QPainter;
        label->setGeometry(150, 0, 200, 50);
        font.setPointSize(18);
        font.setFamily("Arial Unicode MS");
        label->setFont(font);
        label->setAttribute(Qt::WA_TranslucentBackground);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setStyleSheet("QLabel {color:white;}");
        //paint(painter, nullptr);
    };
    ~QLabelGraphicsItem(){
        // delete _label;
        delete label;
    }

    QRectF boundingRect() const override {
        return QRectF(0, 0, label->width(), label->height());
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override {
        QPixmap pixmap = label->grab();
        painter->drawPixmap(boundingRect().topLeft(), pixmap);
    }

    void updateScore(int score){
        QString str;
        str.setNum(score);
        label->setText(str);
    }

    void resetFontSize(int size){
        font.setPointSize(size);
        label->setFont(font);
    }

    void resetFontBold(bool b){
        font.setBold(b);
        label->setFont(font);
    }

private:
    QLabel* label;
    // QPainter* painter;
    QFont font;
};

#endif // QLABELGRAPHICSITEM_H
