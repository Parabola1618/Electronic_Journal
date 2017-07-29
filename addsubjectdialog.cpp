#include "addsubjectdialog.h"
#include "ui_addsubjectdialog.h"

addSubjectDialog::addSubjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSubjectDialog)
{
    ui->setupUi(this);
}

addSubjectDialog::~addSubjectDialog()
{
    delete ui;
}

QString addSubjectDialog::subjectName() const
{
    return ui->subjectName->text();

}

void addSubjectDialog::clear()
{
    ui->subjectName->clear();
}
