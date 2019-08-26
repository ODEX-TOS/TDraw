#ifndef DRAW_H
#define DRAW_H

#include <QList>
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
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private:
    void createActions();
    void createMenus();
    bool maybeSave();
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
    QAction *aboutAct;
    QAction *aboutQTAct;

    Ui::Draw *ui;
};

#endif // DRAW_H
