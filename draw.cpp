#include "draw.h"
#include "ui_draw.h"

#include <scribblearea.h>

Draw::Draw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Draw)
{
    ui->setupUi(this);
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);
    createActions();
    createMenus();
    setWindowTitle(tr("TDraw"));
    resize(500,500);
}

Draw::~Draw()
{
    delete ui;
}
