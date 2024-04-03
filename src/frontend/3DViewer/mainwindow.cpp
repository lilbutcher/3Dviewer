#define GL_SILENCE_DEPRECATION
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "myopenglwidget.h"
#include <QVBoxLayout>
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Инициализация класса виджета
    MyOpenGLWidget *openGLWidget = new MyOpenGLWidget(ui->openGLWidget);
    openGLWidget->readSettings();
    //Инициализация данных для отрисовки
    openGLWidget->data3d.amount_polygon = 0;
    openGLWidget->data3d_copy.amount_polygon = 0;
    //Инициализация слайдеров для перемещения
    openGLWidget->MX_slider = ui->MX_horizontalSlider->value();
    openGLWidget->MY_slider = ui->MY_horizontalSlider->value();
    openGLWidget->MZ_slider = ui->MZ_horizontalSlider->value();
    //Инициализация слайдеров для поворота
    openGLWidget->RX_slider = ui->RX_horizontalSlider->value();
    openGLWidget->RY_slider = ui->RY_horizontalSlider->value();
    openGLWidget->RZ_slider = ui->RZ_horizontalSlider->value();
    //Инициализация слайдера для маштабирования
    openGLWidget->Scale_slider = 1;
    ui->Central_radioButton->setChecked(1);
    //Настройка отображения виджета
    QVBoxLayout *layout = new QVBoxLayout(ui->openGLWidget);
    layout->addWidget(openGLWidget);
    ui->openGLWidget->setLayout(layout);
    // Настройка слайдера для перемещения объекта по оси Х
    connect(ui->MX_horizontalSlider, &QSlider::valueChanged, ui->MX_spinBox, &QSpinBox::setValue);
    connect(ui->MX_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->MX_horizontalSlider, &QSlider::setValue);
    ui->MX_spinBox->setMinimum(-500);
    ui->MX_spinBox->setMaximum(500);
    ui->MX_horizontalSlider->setMinimum(-500);
    ui->MX_horizontalSlider->setMaximum(500);
    ui->MX_horizontalSlider->setValue(0);
    // Настройка слайдера для перемещения объекта по оси У
    connect(ui->MY_horizontalSlider, &QSlider::valueChanged, ui->MY_spinBox, &QSpinBox::setValue);
    connect(ui->MY_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->MY_horizontalSlider, &QSlider::setValue);
    ui->MY_spinBox->setMinimum(-500);
    ui->MY_spinBox->setMaximum(500);
    ui->MY_horizontalSlider->setMinimum(-500);
    ui->MY_horizontalSlider->setMaximum(500);
    ui->MY_horizontalSlider->setValue(0);
    // Настройка слайдера для перемещения объекта по оси Z
    connect(ui->MZ_horizontalSlider, &QSlider::valueChanged, ui->MZ_spinBox, &QSpinBox::setValue);
    connect(ui->MZ_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->MZ_horizontalSlider, &QSlider::setValue);
    ui->MZ_spinBox->setMinimum(-500);
    ui->MZ_spinBox->setMaximum(500);
    ui->MZ_horizontalSlider->setMinimum(-500);
    ui->MZ_horizontalSlider->setMaximum(500);
    ui->MZ_horizontalSlider->setValue(0);

    // Настройка слайдера для поворота объекта по оси Х
    connect(ui->RX_horizontalSlider, &QSlider::valueChanged, ui->RX_spinBox, &QSpinBox::setValue);
    connect(ui->RX_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->RX_horizontalSlider, &QSlider::setValue);
    ui->RX_spinBox->setMinimum(-3600000);
    ui->RX_spinBox->setMaximum(3600000);
    ui->RX_horizontalSlider->setMinimum(-1000000);
    ui->RX_horizontalSlider->setMaximum(1000000);
    ui->RX_horizontalSlider->setValue(0);

    // Настройка слайдера для перемещения объекта по оси У
    connect(ui->RY_horizontalSlider, &QSlider::valueChanged, ui->RY_spinBox, &QSpinBox::setValue);
    connect(ui->RY_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->RY_horizontalSlider, &QSlider::setValue);
    ui->RY_spinBox->setMinimum(-3600000);
    ui->RY_spinBox->setMaximum(3600000);
    ui->RY_horizontalSlider->setMinimum(-1000000);
    ui->RY_horizontalSlider->setMaximum(1000000);
    ui->RY_horizontalSlider->setValue(0);

    // Настройка слайдера для перемещения объекта по оси Z
    connect(ui->RZ_horizontalSlider, &QSlider::valueChanged, ui->RZ_spinBox, &QSpinBox::setValue);
    connect(ui->RZ_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->RZ_horizontalSlider, &QSlider::setValue);
    ui->RZ_spinBox->setMinimum(-3600000);
    ui->RZ_spinBox->setMaximum(3600000);
    ui->RZ_horizontalSlider->setMinimum(-1000000);
    ui->RZ_horizontalSlider->setMaximum(1000000);
    ui->RZ_horizontalSlider->setValue(0);
    // Настройка слайдера для маштабирования объекта
    connect(ui->Scale_horizontalSlider, &QSlider::valueChanged, ui->Scale_spinBox, &QSpinBox::setValue);
    connect(ui->Scale_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->Scale_horizontalSlider, &QSlider::setValue);
    ui->Scale_spinBox->setMinimum(1);
    ui->Scale_spinBox->setMaximum(100);
    ui->Scale_horizontalSlider->setMinimum(1);
    ui->Scale_horizontalSlider->setMaximum(100);
    ui->Scale_horizontalSlider->setValue(100);

}

MainWindow::~MainWindow()
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    openGLWidget->writeSettings();
    //Высвобождение памяти
    freeAllData(&openGLWidget->data3d);
    freeAllData(&openGLWidget->data3d_copy);
    delete ui;
}

void MainWindow::on_OpenButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(nullptr, "Открыть файл", "", "Файлы (*.obj *.stl)");
       ui->FileName_2->setText(filename);

       MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
       openGLWidget->data3d = data_preparation(filename.toStdString().c_str());
       openGLWidget->data3d_copy = data_preparation(filename.toStdString().c_str());
       // for (int i = 0; i < openGLWidget->data3d.v->amount_vert; i++) {
       //  printf("v %f %f %f \n", openGLWidget->data3d.v->coord[i].x, openGLWidget->data3d.v->coord[i].y,
       //         openGLWidget->data3d.v->coord[i].z);
       // }
       if (openGLWidget) {
           openGLWidget->setObjFilePath(filename);
           openGLWidget->update(); // вызов метода paintGL() для обновления отображения
           ui->Vertexes_num->setText(QString::number(openGLWidget->data3d.v->amount_vert));
           ui->Polygons_num->setText(QString::number(openGLWidget->data3d.amount_polygon));
       }

}


void MainWindow::on_Apply_button_clicked()
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
        if (openGLWidget) {
            openGLWidget->data3d = turnX(&openGLWidget->data3d, ui->RX_spinBox->value()); //Поворот координат по оси х
            openGLWidget->data3d = turnY(&openGLWidget->data3d, ui->RY_spinBox->value()); //Поворот координат по оси y
            openGLWidget->data3d = turnZ(&openGLWidget->data3d, ui->RZ_spinBox->value()); //Поворот координат по оси z
            openGLWidget->data3d = moveObj(&openGLWidget->data3d, ui->MX_spinBox->value(), ui->MY_spinBox->value(), ui->MZ_spinBox->value()); // Перемещение объекта
            openGLWidget->update(); // вызов метода paintGL()
        }
}

//  Обработка движения слайдера для перемещения по Х
void MainWindow::on_MX_horizontalSlider_sliderMoved(int position)
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
            openGLWidget->data3d = moveObj(&openGLWidget->data3d, position - openGLWidget->MX_slider, 0, 0); // Перемещение объекта
            openGLWidget->update(); // вызов метода paintGL()
            openGLWidget->MX_slider = position;
}
// Обработка движения слайдера для перемещения по Y
void MainWindow::on_MY_horizontalSlider_sliderMoved(int position)
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
            openGLWidget->data3d = moveObj(&openGLWidget->data3d, 0, position - openGLWidget->MY_slider, 0); // Перемещение объекта
            openGLWidget->update(); // вызов метода paintGL()
            openGLWidget->MY_slider = position;
}

// Обработка движения слайдера для перемещения по Z
void MainWindow::on_MZ_horizontalSlider_sliderMoved(int position)
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
     if (openGLWidget->central){
    openGLWidget->data3d = moveObj(&openGLWidget->data3d, 0, 0, position - openGLWidget->MZ_slider); // Перемещение объекта
    openGLWidget->update(); // вызов метода paintGL()
    openGLWidget->MZ_slider = position;
    }
}

// Обработка движения слайдера для кручения по Х
void MainWindow::on_RX_horizontalSlider_sliderMoved(int position)
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
            openGLWidget->data3d = turnX(&openGLWidget->data3d, (position - openGLWidget->RX_slider) / 1000); // Поворот объекта
            openGLWidget->update(); // вызов метода paintGL()
            openGLWidget->RX_slider = position;
}

// Обработка движения слайдера для кручения по Y
void MainWindow::on_RY_horizontalSlider_sliderMoved(int position)
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
            openGLWidget->data3d = turnY(&openGLWidget->data3d, (position - openGLWidget->RY_slider) / 1000); // Поворот объекта
            openGLWidget->update(); // вызов метода paintGL()
            openGLWidget->RY_slider = position;
}

// Обработка движения слайдера для кручения по Z
void MainWindow::on_RZ_horizontalSlider_sliderMoved(int position)
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
            openGLWidget->data3d = turnZ(&openGLWidget->data3d, (position - openGLWidget->RZ_slider) / 1000); // Поворот объекта
            openGLWidget->update(); // вызов метода paintGL()
            openGLWidget->RZ_slider = position;
}

// Обработка движения слайдера для маштабирования
void MainWindow::on_Scale_horizontalSlider_sliderMoved(int position)
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    if(position < openGLWidget->Scale_slider)
        openGLWidget->data3d = scaleObj(&openGLWidget->data3d_copy,  (double) (position) / 100); // Маштабирование объекта
    else
        openGLWidget->data3d = scaleObj(&openGLWidget->data3d_copy,  (double) (position) / 100 + 1); // Маштабирование объекта
    openGLWidget->update(); // вызов метода paintGL()
    openGLWidget->Scale_slider = position;
}


void MainWindow::on_Parallel_radioButton_clicked(bool checked)
{
     MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    if(checked){
        openGLWidget->parallel = true;
        openGLWidget->central = false;
    }
        openGLWidget->update(); // вызов метода paintGL()
}


void MainWindow::on_Central_radioButton_clicked(bool checked)
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
   if(checked){
       openGLWidget->parallel = false;
       openGLWidget->central = true;
   }
       openGLWidget->update(); // вызов метода paintGL()
}

//Устанвока непрерывной линии
void MainWindow::on_Solid_radioButton_clicked()
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    openGLWidget->solid_edge = true;
    openGLWidget->update(); // вызов метода paintGL()
}

//Устанвока прерывистой линии
void MainWindow::on_Dashed_radioButton_clicked()
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    openGLWidget->solid_edge = false;
    openGLWidget->update(); // вызов метода paintGL()
}

//Смена ширины линий
void MainWindow::on_line_width_valueChanged(int arg1)
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    openGLWidget->line_width = ui->line_width->value();
    openGLWidget->update(); // вызов метода paintGL()
}
//Смена цвета ребер
void MainWindow::on_choose_color_line_clicked()
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    openGLWidget->line_color = QColorDialog::getColor(Qt::white, this, tr("Select color"));
    openGLWidget->update(); // вызов метода paintGL()
}

//Смена цвета вершин
void MainWindow::on_choose_color_vertex_clicked()
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    openGLWidget->vertex_color = QColorDialog::getColor(Qt::white, this, tr("Select color"));
    openGLWidget->update(); // вызов метода paintGL()
}

//Смена заднего фона
void MainWindow::on_choose_color_background_clicked()
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    openGLWidget->background_color = QColorDialog::getColor(Qt::white, this, tr("Select color"));
    openGLWidget->update(); // вызов метода paintGL()
}

//Смена размера вершин
void MainWindow::on_spinBox_vertex_size_valueChanged(int arg1)
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    openGLWidget->vertex_size = ui->spinBox_vertex_size->value();
    openGLWidget->update(); // вызов метода paintGL()
}


void MainWindow::on_Non_radioButton_clicked()
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    openGLWidget->vertex_non = true;
    openGLWidget->update(); // вызов метода paintGL()
}


void MainWindow::on_Circle_radioButton_clicked()
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    openGLWidget->vertex_circle = true;
    openGLWidget->vertex_non = false;
    openGLWidget->vertex_square = false;
    openGLWidget->update(); // вызов метода paintGL()
}


void MainWindow::on_Square_radioButton_clicked()
{
    MyOpenGLWidget *openGLWidget = ui->openGLWidget->findChild<MyOpenGLWidget*>();
    openGLWidget->vertex_circle = false;
    openGLWidget->vertex_non = false;
    openGLWidget->vertex_square = true;
    openGLWidget->update(); // вызов метода paintGL()
}


void MainWindow::on_ScreenshotButton_clicked()
{

    QString str = QFileDialog::getSaveFileName(
        this, nullptr, nullptr, "JPEG (*.jpeg) ;; BMP (*.bmp");

    if (!str.isEmpty()) {
       ui->openGLWidget->grab().save(str);
    }
}


void MainWindow::on_RecordingButton_clicked()
{
    frames = 0;
    gif = new QGifImage;
    timer = new QTimer(this);

    gif->setDefaultDelay(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(saveGif()));
    timer->start(100);
}

void MainWindow::saveGif() {
    QPixmap pix = QPixmap::fromImage(ui->openGLWidget->grab().toImage());
    QPixmap scaledPix = pix.scaled(QSize(640, 480), Qt::IgnoreAspectRatio,
                                   Qt::SmoothTransformation);
    gif->addFrame(scaledPix.toImage());

    if (frames == 50) {
       timer->stop();
       QString pathGIF = QFileDialog::getSaveFileName(
           this, ("Save as GIF"), "image.gif", "GIF Image Files (*.gif)");

       if (!pathGIF.isEmpty() && !pathGIF.isNull()) {
           gif->save(pathGIF);
           delete timer;
           delete gif;
       } else {
           delete timer;
           delete gif;
       }
    }
    frames++;
}

