#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class ScribbleArea : public QWidget {
    Q_OBJECT

public:
    ScribbleArea(QWidget *parent = nullptr);
    bool openImage(const QString &filename);
    bool saveImage(const QString &filename, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);

    // returns if the drawing area has been modified
    bool isModified() const {return modified;}

    // returns the pen color
    QColor PenColor() const {return penColor;}

    // returns the pen width
    int PenWidth() const { return penWidth;}

public slots:
    void clearImage();
    void print();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    bool modified;
    bool isDrawing;
    QColor penColor;
    QImage image;
    int penWidth;
    QPoint lastPoint;

};

#endif // SCRIBBLEAREA_H
