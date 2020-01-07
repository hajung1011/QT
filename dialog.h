#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QObject>
#include <QMouseEvent>
#include <QCoreApplication>
#include <time.h>
#include "graph.h"
#include "traceroute.h"

#define radius 50
#define VERTEX 22
#define END 21

class Graph;
class TraceRoute;

namespace Ui { class Dialog; }

typedef struct VertexInfo
{
    int index;
    double x;
    double y;
}VertexInfo;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    // scene background
    Ui::Dialog *ui;
    QString MainPath;
    void SetView();

    // create graph and mapping
    Graph* graph;
    int vertex;
    int **matrix;
    VertexInfo* info;
    int start_vertex;
    int end_vertex;
    void SetVertexInfo();
    void DrawVertex();

    // traceroute
    TraceRoute* trace;
    const int* result_traceroute;
    int result_traceroute_size;
    void SetResult();
    void DrawPath();

    // QGraphicsItem
    QGraphicsScene *scene;
    QList<QGraphicsEllipseItem*> vertex_list;   // mapping vertex
    QList<QGraphicsTextItem*> vertex_text;
    QList<QGraphicsEllipseItem*> path_vertex;   // path
    QList<QGraphicsTextItem*> path_text;
    QList<QGraphicsLineItem*> path_edge;
    QGraphicsPixmapItem* fire_pixmapitem;       // fire
    QPointF fire_point;
    QMessageBox msgbox; // msgbox

    // error
    void MessageboxIndexError();
    void MessageboxPointError();
    void MessageboxBlankError();
    void MessageboxPathError();
    void MessageboxImageError();

};
#endif // DIALOG_H
