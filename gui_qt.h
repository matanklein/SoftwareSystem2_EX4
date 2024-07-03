#ifndef GUI_QT_H
#define GUI_QT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class gui_qt; }
QT_END_NAMESPACE

class gui_qt : public QMainWindow
{
    Q_OBJECT

public:
    gui_qt(QWidget *parent = nullptr);
    ~gui_qt();

private:
    Ui::gui_qt *ui;
};
#endif // GUI_QT_H
