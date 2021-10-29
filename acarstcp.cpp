#include "acarstcp.h"
#include "ui_acarstcp.h"

acarstcp::acarstcp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acarstcp)
{
    ui->setupUi(this);
}

acarstcp::~acarstcp()
{
    delete ui;
}
