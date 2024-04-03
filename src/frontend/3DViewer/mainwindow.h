#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define GL_SILENCE_DEPRECATION


#include <QMainWindow>
#include <QOpenGLWidget>
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QDebug>
#include <QSettings>
#include <QThread>
#include <QTimer>

#include "QtGifImage/gifimage/qgifimage.h"

extern "C" {
#include "QtGifImage/gifimage/qgifimage.h"
}


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenButton_clicked();
    void on_Apply_button_clicked();

    void on_MX_horizontalSlider_sliderMoved(int position);

    void on_MY_horizontalSlider_sliderMoved(int position);

    void on_MZ_horizontalSlider_sliderMoved(int position);

    void on_RX_horizontalSlider_sliderMoved(int position);

    void on_RY_horizontalSlider_sliderMoved(int position);

    void on_RZ_horizontalSlider_sliderMoved(int position);

    void on_Scale_horizontalSlider_sliderMoved(int position);

    void on_Parallel_radioButton_clicked(bool checked);

    void on_Central_radioButton_clicked(bool checked);

    void on_Solid_radioButton_clicked();

    void on_Dashed_radioButton_clicked();

    void on_line_width_valueChanged(int arg1);

    void on_choose_color_line_clicked();

    void on_choose_color_vertex_clicked();

    void on_choose_color_background_clicked();

    void on_spinBox_vertex_size_valueChanged(int arg1);

    void on_Non_radioButton_clicked();

    void on_Circle_radioButton_clicked();

    void on_Square_radioButton_clicked();

    void on_ScreenshotButton_clicked();

    void on_RecordingButton_clicked();

    void saveGif();

private:
    Ui::MainWindow *ui;
    QGifImage* gif;
    QTimer* timer;
    int frames;
};
#endif // MAINWINDOW_H
