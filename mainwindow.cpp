#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QGuiApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionSave->setEnabled(false);
    ui->actionSaveAs->setEnabled(false);
    ui->actionAddMark->setEnabled(false);
    ui->actionAddStudent->setEnabled(false);

    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(open()) );
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(save()) );
    connect(ui->actionSaveAs, SIGNAL(triggered(bool)), this, SLOT(saveAs()) );

    connect(ui->subjects, SIGNAL(currentIndexChanged(int)), this, SLOT(subjectChange(int)) );
    connect(ui->tableStudents, SIGNAL(cellChanged(int,int)), this, SLOT(editTableStudents(int, int)) );
    connect(ui->tableMarks, SIGNAL(cellChanged(int,int)), this, SLOT(editTableMarks(int, int)) );

    connect(ui->actionAddStudent, SIGNAL(triggered(bool)), this, SLOT(addNewStudent()) );
    connect(ui->actionAddMark, SIGNAL(triggered(bool)), this, SLOT(addNewMark()) );
    connect(ui->actionAddSubject, SIGNAL(triggered(bool)), this, SLOT(addNewSubject()) );

    manager.setTableStudents(ui->tableStudents);
    manager.setTableMarks(ui->tableMarks);
    manager.setComboBoxSubjects(ui->subjects);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "../ElelectronicJournal", tr("Text files (*.txt)") );
    if(!fileName.isNull() )
    {
        if(manager.loadFile(fileName) )
        {
            statusBar()->showMessage(tr("File opened"));
            ui->actionSave->setEnabled(true);
            ui->actionSaveAs->setEnabled(true);
            ui->actionAddMark->setEnabled(true);
            ui->actionAddStudent->setEnabled(true);
        }
        else QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                      tr("Cannot open %1")
                                      .arg(QDir::toNativeSeparators(fileName)) );
    }
}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "../ElelectronicJournal", tr("Text files(*.txt)") );
    if(manager.writeToFile(fileName) )
    {
        statusBar()->showMessage("File saved");
        _fileName = fileName;
    }
    else QMessageBox::information(this, QGuiApplication::applicationDisplayName() ,
                                  tr("Cannot save %1 ")
                                  .arg(QDir::toNativeSeparators(fileName)) );
}

void MainWindow::save()
{
    if(_fileName.isEmpty() )
        saveAs();
    else
    {
        if(manager.writeToFile(_fileName) )
        {
            statusBar()->showMessage("File saved");
        }
        else QMessageBox::information(this, QGuiApplication::applicationDisplayName() ,
                                      tr("Cannot save %1 ")
                                      .arg(QDir::toNativeSeparators(_fileName)) );
    }
}

void MainWindow::subjectChange(int newIndex)
{
    manager.updateTableMarks(newIndex);
}

void MainWindow::addNewMark()
{
    int subjectsQuantity =manager.subjectsQuantity();
    int studentsQuantity = manager.studentsQuantity();
    manager.setMarksQuantity(manager.marksQuantity() + 1);

    vectorMarks tempMarks = manager.marks();
    for(int i = 0; i < subjectsQuantity; ++i)
    {
        for(int j = 0; j < studentsQuantity; ++j)
        {
            tempMarks[i][j].push_back(0);
        }
    }
    manager.setMarks(tempMarks);

    manager.updateTableMarks(ui->subjects->currentIndex());
}


void MainWindow::addNewStudent()
{
    addDialog.exec();
    if(addDialog.result() == QDialog::Accepted)
    {
        manager.setStudentsQuantity(manager.studentsQuantity() + 1);

        QVector<QString> tempStudents = manager.students();
        tempStudents.push_back(addDialog.sendData() );
        manager.setStudents(tempStudents);

        vectorMarks tempMarks = manager.marks();
        int subjectsQuantity = manager.subjectsQuantity();
        QVector<int> tempVec(manager.marksQuantity(), 0);
        for(int i = 0; i < subjectsQuantity; ++i)
        {
            tempMarks[i].push_back(tempVec);
        }

        manager.setMarks(tempMarks);

        manager.updateTableStudents();
        manager.updateTableMarks(ui->subjects->currentIndex());

        addDialog.clear();
    }
    else QMessageBox::information(this, QGuiApplication::applicationDisplayName(), tr("Cannot add new student") );
}


void MainWindow::addNewSubject()
{
    newSubjectDialog.exec();
    if(newSubjectDialog.result() == QDialog::Accepted)
    {
        QVector<QString> tempSubjects = manager.subjects();
        vectorMarks tempMarks = manager.marks();

        if(manager.subjectsQuantity() == 0)
        {
            manager.setSubjectsQuantity(1);
            manager.setMarksQuantity(1);
            manager.setStudentsQuantity(1);

            tempSubjects.push_back(newSubjectDialog.subjectName());
            tempMarks.resize(1);
            tempMarks[0].resize(1);
            tempMarks[0][0].push_back(0);

            QVector<QString> tempStudents = manager.students();
            tempStudents.push_back("");
            manager.setStudents(tempStudents);
        }
        else
        {
            int studentsQuantity = manager.studentsQuantity();
            int subjectsQuantity = manager.subjectsQuantity();
            int marksQuantity = manager.marksQuantity();
            ++subjectsQuantity;
            manager.setSubjectsQuantity(subjectsQuantity);
            tempSubjects.push_back(newSubjectDialog.subjectName());

            tempMarks.resize(subjectsQuantity);
            tempMarks[subjectsQuantity - 1].resize(studentsQuantity);

            for(int i = 0; i < studentsQuantity; ++i)
            {
                tempMarks[subjectsQuantity - 1][i].resize(marksQuantity);
                tempMarks[subjectsQuantity - 1][i].fill(0);
            }
        }

        manager.setMarks(tempMarks);
        manager.setSubjects(tempSubjects);

        ui->actionSave->setEnabled(true);
        ui->actionSaveAs->setEnabled(true);
        ui->actionAddMark->setEnabled(true);
        ui->actionAddStudent->setEnabled(true);
        newSubjectDialog.clear();
        manager.addSubjectComboBox();
        manager.updateTableStudents();
        //manager.updateTableMarks();
    }
}

void MainWindow::editTableStudents(int row, int col)
{
    QVector<QString> tempStudents = manager.students();
    tempStudents[row] = ui->tableStudents->item(row, col)->text();
    manager.setStudents(tempStudents);
}

void MainWindow::editTableMarks(int row, int col)
{
    vectorMarks tempMarks = manager.marks();
    tempMarks[ui->subjects->currentIndex()][row][col] = ui->tableMarks->item(row, col)->text().toInt();
    manager.setMarks(tempMarks);
}
