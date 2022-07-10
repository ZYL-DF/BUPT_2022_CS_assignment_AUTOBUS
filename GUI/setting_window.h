#ifndef SETTING_WINDOW_H
#define SETTING_WINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include <QDialogButtonBox>
namespace Ui {
class setting_window;
}

class setting_window : public QDialog
{
    Q_OBJECT

public:
    explicit setting_window(QWidget *parent = nullptr);
    ~setting_window();

private:
    Ui::setting_window *ui;
    void paintEvent(QPaintEvent *);
    QPixmap setting_background;

signals:
void theme_changed();

public slots:

    void setvalue();
private slots:




    void on_pushButton_accept_clicked();
    void on_pushButton_cancel_clicked();
};

#endif // SETTING_WINDOW_H
