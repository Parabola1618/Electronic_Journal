#include "addstudentdialog.h"
#include "ui_addstudentdialog.h"

addStudentDialog::addStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStudentDialog)
{
    ui->setupUi(this);
}

addStudentDialog::~addStudentDialog()
{
    delete ui;
}

QString addStudentDialog::sendData() const
{
    QString result(ui->lineEditSurname->text() + " " + ui->lineEditName->text());
    return result;
}

void addStudentDialog::clear()
{
    ui->lineEditSurname->clear();
    ui->lineEditName->clear();
}

