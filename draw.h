#ifndef DRAW_H
#define DRAW_H

#include <QList>
#include <QFileDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QImageWriter>
#include <QMainWindow>

namespace Ui {
class Draw;
}
class ScribbleArea;

class Draw : public QMainWindow
{
    Q_OBJECT

public:
    explicit Draw(QWidget *parent = nullptr);
    ~Draw() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // open a file slot
    void open();

    // save a file slot
    void save();

    // set the pen color slot
    void penColor();

    // set the pen width slot
    void penWidth();

    // open the about page slot
    void about();

private:
    //populate all the available actions
    void createActions();

    // populate all the available menus
    void createMenus();

    // check if there are changes to the picture
    bool maybeSave();

    // save a file. returns if the save was succesfull
    bool saveFile(const QByteArray &fileFormat);

    ScribbleArea *scribbleArea;
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;
    QAction *openAction;
    QList<QAction *> saveAsActs;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQTAct;

    Ui::Draw *ui;
};

#endif // DRAW_H
