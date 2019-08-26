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

void Draw::closeEvent(QCloseEvent *event){
    if(maybeSave()){
        event->accept();
    }else {
        event->ignore();
    }
}

void Draw::open(){
    if(maybeSave()){
        QString filename = QFileDialog::getOpenFileName(this, tr("open File"), QDir::currentPath());
        if(!filename.isEmpty()){
            scribbleArea->openImage(filename);
        }
    }
}

void Draw::save(){
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileformat = action->data().toByteArray();
    saveFile(fileformat);
}

void Draw::penColor(){
    QColor newColor = QColorDialog::getColor(scribbleArea->PenColor());
    if (newColor.isValid()){
        scribbleArea->setPenColor(newColor);
    }
}

void Draw::penWidth(){
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Draw"), tr("Select pen width"), scribbleArea->PenWidth(), 1, 50, 1, &ok);
    if(ok){
        scribbleArea->setPenWidth(newWidth);
    }
}

void Draw::about(){
    QMessageBox::about(this, tr("About"), tr("<p>The <b>TOS</b> drawing tool is build for the TOS OS."
                                             " This drawing app is made to work with tiling window managers.</p>"));
}

Draw::~Draw()
{
    delete ui;
}
