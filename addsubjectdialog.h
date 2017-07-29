#ifndef ADDSUBJECTDIALOG_H
#define ADDSUBJECTDIALOG_H

#include <QDialog>

namespace Ui {
class addSubjectDialog;
}

class addSubjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addSubjectDialog(QWidget *parent = 0);
    ~addSubjectDialog();
    QString subjectName() const;
    void clear();

private:
    Ui::addSubjectDialog *ui;
};

#endif // ADDSUBJECTDIALOG_H
