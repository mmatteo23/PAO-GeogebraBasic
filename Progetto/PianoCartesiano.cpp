#include "PianoCartesiano.h"

PianoCartesiano::PianoCartesiano(WorkSpace* w, QWidget *parent) :
    QWidget(parent), pixelScale(15), workspace(w)
{}

void PianoCartesiano::paintEvent(QPaintEvent* e) {
    int side = qMin(width(), height());

    QPainter p(this);
    p.setViewport((width()-side)/2, (height()-side)/2, side, side);
    p.setWindow(-400,-400,800,800);

    QPen pen;
    pen.setWidth(0);
    pen.setColor(QColor::fromRgb(217, 217, 217));
    p.setPen(pen);

    //griglia main
    if(pixelScale > 5){
        for (int i=-side; i<side; ++i) {
            p.drawLine(side, i*pixelScale/5, -side, i*pixelScale/5);
            p.drawLine(i*pixelScale/5, side, i*pixelScale/5, -side);
        }
    }

    pen.setColor(QColor::fromRgb(186, 186, 186));
    pen.setWidth(0);
    p.setPen(pen);

    unsigned int fontSize = 2;
    if(pixelScale<10)
        fontSize = 2;

    //trattini grigi
    for (int i=-side; i<side; ++i) {
        pen.setColor(QColor::fromRgb(186, 186, 186));
        pen.setWidth(0);
        p.setPen(pen);
        p.drawLine(i*pixelScale, side, i*pixelScale, -side);
        p.drawLine(side, i*pixelScale, -side, i*pixelScale);
        p.setPen(Qt::black);
        p.setFont(QFont(QString("Verdana"), fontSize));
        p.drawText(i*pixelScale+1, 4, QString::fromStdString(std::to_string(i))); // numeri asse x
        if(i!=0) p.drawText(-3, i*pixelScale, QString::fromStdString(std::to_string(-i))); // numeri asse y
    }

    //----------------------------------//

    pen.setWidth(1);
    for(auto& i : workspace->getDisegni()) {
        pen.setColor(QString::fromStdString(i.get()->getColore()));
        p.setPen(pen);
        i.get()->disegna(&p, pixelScale);
    }

    //----------------------------------//

    pen.setWidth(0);
    pen.setColor(Qt::black);
    p.setPen(pen);

    //asse x
    p.drawLine(-side,0,side,0);
    //asse y
    p.drawLine(0,side,0,-side);

    QWidget::paintEvent(e);
}

void PianoCartesiano::modificaScala(int val) {
    if(pixelScale > 10 || val > 0){
        pixelScale += val;
        refresh();
    }
}

void PianoCartesiano::refresh() {
    setUpdatesEnabled(true);
    update();
}

void PianoCartesiano::setWorkspace(WorkSpace *w) {
    workspace = w;
}

bool PianoCartesiano::pianocartesianoVuoto() const
{
    return workspace->workspaceVuota();
}
