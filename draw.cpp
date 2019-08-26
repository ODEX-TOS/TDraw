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

void Draw::createActions(){
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    foreach (QByteArray format , QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcut(QKeySequence::Print);
    connect(printAct, SIGNAL(triggered()), scribbleArea, SLOT(print()));

    exitAct = new QAction(tr("&Exit..."), this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    // TODO: add a shortcut for selecting a pen color
    penColorAct = new QAction(tr("&Pen Color..."), this);
    penColorAct->setShortcut(tr("Ctrl+Alt+C"));
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    // TODO: add a shortcut for selecting a pen width
    penWidthAct = new QAction(tr("&Pen Width..."), this);
    penWidthAct->setShortcut(tr("Ctrl+Alt+W"));
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearScreenAct = new QAction(tr("&Clear screen..."), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()), scribbleArea, SLOT(clearImage()));

    aboutAct = new QAction(tr("&About..."), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQTAct = new QAction(tr("About &qt..."), this);
    connect(aboutQTAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}

void Draw::createMenus(){
    saveAsMenu = new QMenu(tr("Save as"), this );

    foreach(QAction *action, saveAsActs){
        saveAsMenu->addAction(action);
    }

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAction);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionsMenu = new QMenu(tr("&Options"), this);
    optionsMenu->addAction(penColorAct);
    optionsMenu->addAction(penWidthAct);
    optionsMenu->addSeparator();
    optionsMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQTAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionsMenu);
    menuBar()->addMenu(helpMenu);

}

bool Draw::maybeSave(){
    if (scribbleArea->isModified()){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("TDraw"), tr("The image has been modified\n"
                                                         "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save){
            return saveFile("png");
        } else if ( ret ==QMessageBox::Cancel){
            return false;
        }
    }
    return true;
}

bool Draw::saveFile(const QByteArray &fileFormat){
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;
    QString filename = QFileDialog::getSaveFileName(this, tr("Save As"), initialPath,
                                                    tr("%1 Files (*.%2);; All Files(*)")
                                                    .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                    .arg(QString::fromLatin1(fileFormat.toUpper())));
    if(!filename.isEmpty()){
        return false;
    }
    return scribbleArea->saveImage(filename, fileFormat.constData());
}

Draw::~Draw()
{
    delete ui;
}
