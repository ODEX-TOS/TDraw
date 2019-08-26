#ifndef DRAW_H
#define DRAW_H

#include <QMainWindow>

namespace Ui {
class Draw;
}

class Draw : public QMainWindow
{
    Q_OBJECT

public:
    explicit Draw(QWidget *parent = nullptr);
    ~Draw();

private:
    Ui::Draw *ui;
};

#endif // DRAW_H
