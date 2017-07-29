#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>

namespace Ui {
class addStudentDialog;
}

class addStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addStudentDialog(QWidget *parent = 0);
    ~addStudentDialog();
    QString sendData() const;

    void clear();

private:
    Ui::addStudentDialog *ui;

};

#endif // ADDSTUDENTDIALOG_H
