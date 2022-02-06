#include "principal.h"
#include <QTranslator>
#include <QApplication>
#include <QLocale>
#include <QtDebug>

int main(int argc, char *argv[])
{
    qDebug ()<<QLocale::system().name();
    QApplication a(argc, argv);
    // Objeto para manejar las traducciones
        QTranslator traducion;
        // Solicitando al usuario que seleccione un idioma
        QString idioma=QLocale::system().name();
        // Dependiendo del idioma seleccionado, carga el archivo de rtaducción
        if (idioma == "ca_ES"){
            traducion.load(":/principal_cat.qm");
        }else if (idioma == "de_DE"){
            traducion.load(":/principal_al.qm");
        }
        // Si es diferente de español, se instala la traducción en TODA la aplicación
        if (idioma != "es_Es"){
                a.installTranslator(&traducion);
            }
    Principal w;
    w.show();
    return a.exec();
}
