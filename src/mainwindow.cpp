#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->savedir_le->setText(DEFAULT_SAVE_DIR);



    // check if savedir exists
    check_savedir_isValid();

    qDebug() << "deubg1";


    connect(ui->convert_btn,SIGNAL(clicked(bool)),this,SLOT(convert_btn()));

    connect(convertprocess,SIGNAL(readyReadStandardOutput()), this, SLOT(show_process_output()));
    connect(convertprocess,SIGNAL(readyReadStandardError()), this , SLOT(show_process_erroutput()));


    qDebug() << "debug2";

}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::check_savedir_isValid(){
    QString savedir_path = ui->savedir_le->text();

    QDir savedir(savedir_path);

    if(!savedir.exists()){

        ui->statusBar->showMessage("save dir doesn't exist");
        return false;

    }

    return true;

}

void MainWindow::convert_btn(){
    bool result = convert_btn_main();
    if(result){
        ui->statusBar->showMessage("convert finished!");
    }
    else{
        ui->statusBar->showMessage("convert failed");
    }
}

bool MainWindow::convert_btn_main(){
    QString link = ui->youtubelink_le->text();

    QString cmd = "youtube-dl -x --audio-format mp3 --embed-thumbnail --add-metadata " + link;

    qDebug() << cmd;

//    convertprocess = new QProcess(this);

    convertprocess->start(cmd);

    convertprocess->waitForFinished();

    qDebug() << convertprocess->exitCode();

    qDebug() << convertprocess->exitStatus();

    if(convertprocess->exitCode()!=0){
        return false;
    }

    return true;


}


void MainWindow::show_process_output(){
    qDebug() << convertprocess->readAllStandardOutput();
    ui->statusBar->showMessage(convertprocess->readAllStandardOutput());
}


void MainWindow::show_process_erroutput(){
    qDebug() << convertprocess->readAllStandardError();
    ui->statusBar->showMessage(convertprocess->readAllStandardError());
}
