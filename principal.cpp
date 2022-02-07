#include "principal.h"
#include "ui_principal.h"

#include <QDebug>
#define DEFAULT_ANCHO 3

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    m_ancho = DEFAULT_ANCHO;
    opc = 1;
    m_imagen = new QImage(this->size(), QImage::Format_ARGB32_Premultiplied);
    m_imagen->fill(Qt::white);
    m_painter = new QPainter(m_imagen);


}

Principal::~Principal()
{
    delete ui;
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    QPen pincel;
    pincel.setColor(m_color);
    pincel.setWidth(m_ancho);
    if(opc == 1){pInicial = event->pos();
    }else if(opc == 2){
        if(m_toogle){
            pInicial = event->pos();
        }else{
            pFinal = event->pos();
            m_painter->setPen(pincel);
            m_painter->drawLine(pInicial, pFinal);
            update();
        }
    }else if(opc == 3){
            if (m_toogle){
                pInicial = event->pos();
            }else {
                pFinal = event->pos();
                QPen pincel;
                pincel.setColor(m_color);
                pincel.setWidth(m_ancho);
                m_painter->setPen(pincel);                
                m_painter->drawRect(pInicial.x(), pInicial.y(), pFinal.x()-pInicial.x(), pFinal.y()-pInicial.y());
                update();
            }
    }else if (opc == 4){
        if(m_toogle){
            pInicial = event->pos();
        }else{
            pFinal = event->pos();
            m_painter->setPen(pincel);
            m_painter->drawEllipse(pInicial.x(), pInicial.y(), pFinal.x()-pInicial.x(), pFinal.y()-pInicial.y());
            update();
        }
    }
    m_toogle = !m_toogle;
}

void Principal::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.drawImage(0,0, *m_imagen);
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{
     if(opc == 1){
        pFinal = event->pos();
        QPen pincel;
        pincel.setWidth(m_ancho);
        pincel.setColor(m_color);
        m_painter->setPen(pincel);
        m_painter->drawLine(pInicial, pFinal);
    }
    update();
    pInicial = pFinal;
}


void Principal::on_actionCerrar_triggered()
{
    close();
}

void Principal::on_actionNuevo_triggered()
{
    m_imagen->fill(Qt::white);
    update();
}

void Principal::on_actionGuardar_triggered()
{
    QDir directorio = QDir::home();
    QString pathArchivo = directorio.absolutePath();
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar proceso creado",
                                                   pathArchivo,
                                                    "Imagen (*.png)");
    if (!fileName.isEmpty())
    {
        m_imagen->save(fileName);
    }
}

void Principal::on_actionColor_triggered()
{
    m_color = QColorDialog::getColor();
}

void Principal::on_actionGrosor_triggered()
{
    m_ancho = QInputDialog::getInt(this, "Ancho del pincel",
                                   "Ingrese el ancho del pincel,",
                                   m_ancho, 1, 50);
}

void Principal::on_actionLibre_triggered()
{
    opc = 1;
}

void Principal::on_actionLinea_triggered()
{
    opc = 2;
    m_toogle = true;
}

void Principal::on_actionRectangulos_triggered()
{
    opc = 3;
    m_toogle = true;
}

void Principal::on_actionCircunferencias_triggered()
{
    opc = 4;
    m_toogle = true;
}
