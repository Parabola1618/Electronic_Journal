#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <journalmanager.h>
#include <addstudentdialog.h>
#include <addsubjectdialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    journalManager manager;
    QString _fileName;
    addStudentDialog addDialog;
    addSubjectDialog newSubjectDialog;

private slots:
    void open();
    void save();
    void saveAs();
    void subjectChange(int newIndex);
    void addNewStudent();
    void addNewMark();
    void addNewSubject();
    void editTableStudents(int row, int col);
    void editTableMarks(int row, int col);
};

#endif // MAINWINDOW_H
