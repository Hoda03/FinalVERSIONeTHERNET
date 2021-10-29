#include "version.h"
#include "ui_version.h"

version::version(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::version)
{
    ui->setupUi(this);
}

version::~version()
{
    delete ui;
}
