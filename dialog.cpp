#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Fire Evacuation Route Simulator");
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    fire_pixmapitem = nullptr;
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(true);

    MainPath = QCoreApplication::applicationDirPath();
    qDebug()<<MainPath;
    SetView();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::SetView()
{

    QString img_path = MainPath + "/IMAGE/map.jpg";
    QImage img(img_path);
    QPixmap pix = QPixmap::fromImage(img);
    pix = pix.scaled(900,580);
    scene->addPixmap(pix);
}

void Dialog::on_pushButton_clicked()
{
    qDebug()<<"PUSH 'GRAPH MAPPING BUTTON'";
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);

    graph = new Graph;
    vertex = VERTEX;
    graph->SetVertex(vertex);
    graph->SetEdge();

    SetVertexInfo();
    DrawVertex();
}

void Dialog::SetVertexInfo()
{
    // Create list and init
    VertexInfo *list = new VertexInfo[vertex];
    for(int i=0;i<vertex;i++)
    {
        list[i].index = i;
        list[i].x = 0;
        list[i].y = 0;
    }
    // list 0
    list[0].index = 0;
    list[0].x = 100;
    list[0].y = 50;
    // list 1
    list[1].index = 1;
    list[1].x = 200;
    list[1].y = 50;
    // list 2
    list[2].index = 2;
    list[2].x = 380;
    list[2].y = 50;
    // list 3
    list[3].index = 3;
    list[3].x = 500;
    list[3].y = 50;
    // list 4
    list[4].index = 4;
    list[4].x = 600;
    list[4].y = 50;
    // list 5
    list[5].index = 5;
    list[5].x = 700;
    list[5].y = 50;
    // list 6
    list[6].index = 6;
    list[6].x = 800;
    list[6].y = 50;
    // list 7
    list[7].index = 7;
    list[7].x = 157;
    list[7].y = 136;
    // list 8
    list[8].index = 8;
    list[8].x = 590;
    list[8].y = 140;
    // list 9
    list[9].index = 9;
    list[9].x = 61;
    list[9].y = 282;
    // list 10
    list[10].index = 10;
    list[10].x = 162;
    list[10].y = 270;
    // list 11
    list[11].index = 11;
    list[11].x = 315;
    list[11].y = 315;
    // list 12
    list[12].index = 12;
    list[12].x = 654;
    list[12].y = 306;
    // list 13
    list[13].index = 13;
    list[13].x = 155;
    list[13].y = 400;
    // list 14
    list[14].index = 14;
    list[14].x = 475;
    list[14].y = 420;
    // list 15
    list[15].index = 15;
    list[15].x = 56;
    list[15].y = 480;
    // list 16
    list[16].index = 16;
    list[16].x = 157;
    list[16].y = 480;
    // list 17
    list[17].index = 17;
    list[17].x = 260;
    list[17].y = 480;
    // list 18
    list[18].index = 18;
    list[18].x = 360;
    list[18].y = 480;
    // list 19
    list[19].index = 19;
    list[19].x = 780;
    list[19].y = 480;
    // list 20
    list[20].index = 20;
    list[20].x = 455;
    list[20].y = 140;
    // list 21,exit
    list[21].index = 21;
    list[21].x = 560;
    list[21].y = 510;

    info = list;
}

void Dialog::DrawVertex()
{
    QBrush vertexBrush(Qt::yellow);
    QPen outlinePen(Qt::white);
    outlinePen.setWidth(1);
    QString index_text = "";

    for(int i = 0; i<VERTEX;i++)
    {
        QGraphicsEllipseItem* ellipse_item = new QGraphicsEllipseItem;
        ellipse_item = scene->addEllipse(info[i].x,info[i].y,radius,radius,outlinePen,vertexBrush);
        vertex_list.append(ellipse_item);

        QGraphicsTextItem* vertex_str = new QGraphicsTextItem;
        index_text = QString::number(info[i].index);
        vertex_str = scene->addText(index_text);
        vertex_str->setPos(info[i].x+(radius/3),info[i].y+(radius/3));
        vertex_text.append(vertex_str);
    }
}

void Dialog::MessageboxIndexError()
{
    msgbox.setText("ERROR : OUT OF INDEX.");
    msgbox.exec();
}

void Dialog::MessageboxPointError()
{
    msgbox.setText("ERROR : SAME VERTEX POINT.");
    msgbox.exec();
}

void Dialog::MessageboxBlankError()
{
    msgbox.setText("ERROR : FILL IN THE BLANK.");
    msgbox.exec();
}

void Dialog::MessageboxPathError()
{
    msgbox.setText("ERROR : NO PATH.");
    msgbox.exec();
}

void Dialog::MessageboxImageError()
{
    msgbox.setText("ERROR : IMAGE ERROR.");
    msgbox.exec();
}

void Dialog::on_pushButton_2_clicked()
{
    qDebug()<<"PUSH 'TRACE ROUTE BUTTON'";

    // Draw Path
    start_vertex = ui->lineEdit->text().toInt();
    end_vertex = END;

    if(ui->lineEdit->text().isEmpty())
    {
        MessageboxBlankError();
    }
    else if(start_vertex>=VERTEX)
    {
          MessageboxIndexError();
    }
    else if(start_vertex == END)
    {
          MessageboxPointError();
    }
    else if(graph->D_EmptyEdge(start_vertex))
    {
        MessageboxPathError();
    }
    else
    {
        // Set Graph Matrix
        graph->SetMatrix();
        matrix = graph->Matrix;

        trace = new TraceRoute(VERTEX);
        trace->set_matrix(matrix);

        qDebug()<<"START : "<<start_vertex;
        qDebug()<<"END : "<<end_vertex;
        SetResult();
    }
}

void Dialog::SetResult()
{
    result_traceroute = nullptr;
    result_traceroute = trace->result(start_vertex,end_vertex,&result_traceroute_size);

    if(result_traceroute_size == 1)   // no path
    {
        MessageboxPathError();
        return;
    }

    ui->pushButton_2->setEnabled(false);
    qDebug()<<"ROUTE :";
    for(int i =0;i<result_traceroute_size;i++)
    {
        qDebug()<<"["<<result_traceroute[i]<<"]";
    }
    qDebug()<<"ROUTE SIZE :"<<result_traceroute_size;

    DrawPath();
}

void Dialog::DrawPath()
{
    // Draw Edge
    QPen linePen(Qt::green);
    linePen.setWidth(3);
    double pos_x1 = 0.0;
    double pos_y1 = 0.0;
    double pos_x2 = 0.0;
    double pos_y2 = 0.0;

    for(int i = 0; i<result_traceroute_size-1;i++)
    {
        int start_i = result_traceroute[i];
        int end_i = result_traceroute[i+1];
        VertexInfo start = info[start_i];
        VertexInfo end = info[end_i];

        // move to center
        pos_x1 = start.x + (radius/2);
        pos_y1 = start.y + (radius/2);
        pos_x2 = end.x + (radius/2);
        pos_y2 = end.y + (radius/2);
        // draw edge line
        QGraphicsLineItem* line_item = new QGraphicsLineItem;
        line_item = scene->addLine(pos_x1,pos_y1,pos_x2,pos_y2,linePen);
        path_edge.append(line_item);
    }

    // Draw Vertex
    for(int i = 0;i<result_traceroute_size;i++)
    {
        int point = result_traceroute[i];

        QBrush vertexBrush(Qt::green);
        QPen outlinePen(Qt::black);
        outlinePen.setWidth(2);
        QString index_text = "";

        QGraphicsEllipseItem* path_item = new QGraphicsEllipseItem;
        path_item = scene->addEllipse(info[point].x,info[point].y,radius,radius,outlinePen,vertexBrush);
        path_vertex.append(path_item);

        QGraphicsTextItem* path_str = new QGraphicsTextItem;
        index_text = QString::number(info[point].index); // +" (" + QString::number(i) + ")";
        path_str = scene->addText(index_text);
        path_str->setPos(info[point].x+(radius/3),info[point].y+(radius/3));
        path_text.append(path_str);
    }
}

void Dialog::on_pushButton_3_clicked()
{
    ui->pushButton_3->setEnabled(false);
    QString fire_img_path = MainPath + "/IMAGE/fire.png";
    fire_pixmapitem = new QGraphicsPixmapItem(QPixmap(fire_img_path));

    int random_point = 0;
    srand(time(nullptr));
    random_point = rand()%19+1;
    switch(random_point)
    {
    case 1:
            graph->DeleteEdge(0, 7); graph->DeleteEdge(7, 0);
            graph->DeleteEdge(0, 9); graph->DeleteEdge(9, 0);
            fire_point.setX(109);
            fire_point.setY(108);
            break;
    case 2:
            graph->DeleteEdge(1, 7); graph->DeleteEdge(7, 1);
            graph->DeleteEdge(1, 20); graph->DeleteEdge(20, 1);
            graph->DeleteEdge(20, 7); graph->DeleteEdge(7, 20);
            fire_point.setX(224);
            fire_point.setY(133);
            break;
    case 3:
            graph->DeleteEdge(9, 7); graph->DeleteEdge(7, 9);
            graph->DeleteEdge(9, 0); graph->DeleteEdge(0, 9);
            fire_point.setX(66);
            fire_point.setY(158);
            // Fire 위치 (66,158) Show
            break;
    case 4:
            graph->DeleteEdge(10, 7); graph->DeleteEdge(7, 10);
            fire_point.setX(172);
            fire_point.setY(211);
            // Fire 위치 (172,211) Show
            break;
    case 5:
            graph->DeleteEdge(2, 7); graph->DeleteEdge(7, 2);
            graph->DeleteEdge(1, 20); graph->DeleteEdge(20, 1);
            graph->DeleteEdge(20, 7); graph->DeleteEdge(7, 20);
            fire_point.setX(343);
            fire_point.setY(139);
            // Fire 위치 (343,139) Show
            break;
    case 6:
            graph->DeleteEdge(20, 7); graph->DeleteEdge(7, 20);
            graph->DeleteEdge(3, 7); graph->DeleteEdge(7, 3);
            graph->DeleteEdge(1, 20); graph->DeleteEdge(20, 1);
            graph->DeleteEdge(2, 20); graph->DeleteEdge(20, 2);
            fire_point.setX(420);
            fire_point.setY(144);
            // Fire 위치 (438,144) Show
            break;
    case 7:
            graph->DeleteEdge(20, 8); graph->DeleteEdge(8, 20);
            fire_point.setX(552);
            fire_point.setY(144);
            // Fire 위치 (552,144) Show
            break;
    case 8:
            graph->DeleteEdge(4, 8); graph->DeleteEdge(8, 4);
            fire_point.setX(613);
            fire_point.setY(109);
            // Fire 위치 (613,109) Show
            break;
    case 9:
            graph->DeleteEdge(5, 8); graph->DeleteEdge(8, 5);
            graph->DeleteEdge(6, 8); graph->DeleteEdge(8, 6);
            fire_point.setX(665);
            fire_point.setY(147);
            // Fire 위치 (665,147) Show
            break;
    case 10:
            graph->DeleteEdge(6, 8); graph->DeleteEdge(8, 6);
            fire_point.setX(773);
            fire_point.setY(146);
            // Fire 위치 (773,146) Show
            break;
    case 11:
            graph->DeleteEdge(12, 8); graph->DeleteEdge(8, 12);
            fire_point.setX(619);
            fire_point.setY(211);
            // Fire 위치 (619,211) Show
            break;
    case 12:
            graph->DeleteEdge(20, 14); graph->DeleteEdge(14, 20);
            fire_point.setX(467);
            fire_point.setY(297);
            // Fire 위치 (467,297) Show
            break;
    case 13:
            graph->DeleteEdge(11, 10); graph->DeleteEdge(10, 11);
            fire_point.setX(249);
            fire_point.setY(298);
            // Fire 위치 (249,298) Show
            break;
    case 14:
            graph->DeleteEdge(13, 10); graph->DeleteEdge(10, 13);
            fire_point.setX(171);
            fire_point.setY(343);
            // Fire 위치 (171,343) Show
            break;
    case 15:
            graph->DeleteEdge(13, 15); graph->DeleteEdge(15, 13);
            fire_point.setX(76);
            fire_point.setY(440);
            // Fire 위치 (76,440) Show
            break;
    case 16:
            graph->DeleteEdge(13, 16); graph->DeleteEdge(16, 13);
            fire_point.setX(182);
            fire_point.setY(452);
            // Fire 위치 (182,452) Show
            break;
    case 17:
            graph->DeleteEdge(13, 17); graph->DeleteEdge(17, 13);
            graph->DeleteEdge(13, 14); graph->DeleteEdge(14, 13);
            graph->DeleteEdge(13, 18); graph->DeleteEdge(18, 13);
            graph->DeleteEdge(14, 17); graph->DeleteEdge(17, 14);
            fire_point.setX(271);
            fire_point.setY(436);
            // Fire 위치 (271,436) Show
            break;
    case 18:
            graph->DeleteEdge(13, 18); graph->DeleteEdge(18, 13);
            graph->DeleteEdge(13, 14); graph->DeleteEdge(14, 13);
            graph->DeleteEdge(14, 17); graph->DeleteEdge(17, 14);
            graph->DeleteEdge(14, 18); graph->DeleteEdge(18, 14);
            fire_point.setX(371);
            fire_point.setY(433);
            // Fire 위치 (371,433) Show
            break;
    case 19:
            graph->DeleteEdge(14, 19); graph->DeleteEdge(19, 14);
            fire_point.setX(808);
            fire_point.setY(435);
            // Fire 위치 (808,435) Show
            break;
    default:
            break;
    }

    if(fire_pixmapitem)
    {
        qDebug()<<"Fire Create at "<<random_point;
        QPointF move(10.0,10.0);
        fire_point -= move;
        fire_pixmapitem->setPos(fire_point);
        scene->addItem(fire_pixmapitem);
    }
    else
    {
        MessageboxImageError();
    }
}

void Dialog::on_pushButton_4_clicked()
{
    qDebug()<<"PUSH 'RESET BUTTON'";
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_2->setEnabled(true);

    start_vertex = 0;

    ui->lineEdit->clear();
    // scene->clear();
    ui->graphicsView->items().clear();

    path_vertex.clear();
    path_text.clear();
    path_edge.clear();

    if(fire_pixmapitem)
    {
        scene->removeItem(fire_pixmapitem);
        fire_pixmapitem = nullptr;
        fire_point.isNull();
    }

    result_traceroute = nullptr;
    result_traceroute_size = 0;

    delete graph;

    graph = new Graph;
    vertex = VERTEX;
    graph->SetVertex(vertex);
    graph->SetEdge();
    SetView();
    DrawVertex();
}

void Dialog::on_pushButton_5_clicked()
{
    this->close();
    delete graph;
    delete trace;
}
