#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDir>
#include <QProcess>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString DEFAULT_SAVE_DIR="/home/chadrick/youtubedownloads";
    bool check_savedir_isValid();
    bool convert_btn_main();
    QProcess* convertprocess = new QProcess(this);

private slots:
    void convert_btn();
    void show_process_output();
    void show_process_erroutput();
};

#endif // MAINWINDOW_H
