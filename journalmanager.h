#ifndef JOURNALMANAGER_H
#define JOURNALMANAGER_H

#include <QString>
#include <QVector>
#include <QTableWidget>
#include <QComboBox>

typedef QVector<QVector<QVector<int> > > vectorMarks;

class journalManager
{
public:
    journalManager();
    bool loadFile(const QString& fileName);
    bool writeToFile(QString fileName) const;

    void updateTableMarks(int subjectNumber);
    void updateTableStudents();
    void updateComboBoxSubjects();
    void addSubjectComboBox();

    void setTableMarks(QTableWidget *tableMarks) { _tableMarks = tableMarks; }
    void setTableStudents(QTableWidget *tableStudents) { _tableStudents = tableStudents; }
    void setComboBoxSubjects(QComboBox *comboBoxSubjects) { _comboBoxSubjects = comboBoxSubjects; }

    void setStudentsQuantity(int studentsQuantity) { _studentsQuantity = studentsQuantity; }
    void setMarksQuantity(int marksQuantity) { _marksQuantity = marksQuantity; }
    void setSubjectsQuantity(int subjectsQuantity) { _subjectsQuantity = subjectsQuantity; }

    void setStudents(QVector<QString> students) { _students = students; }
    void setSubjects(QVector<QString> subjects) { _subjects = subjects; }
    void setMarks(vectorMarks marks) { _marks = marks; }

    int subjectsQuantity() const { return _subjectsQuantity; }
    int studentsQuantity() const { return _studentsQuantity; }
    int marksQuantity() const { return _marksQuantity; }

    vectorMarks marks() const { return _marks; }
    QVector<QString> students() const  { return _students; }
    QVector<QString> subjects() const { return _subjects; }
private:
    QVector<QString> _students;
    QVector<QString> _subjects;
    vectorMarks _marks;

    int _marksQuantity;
    int _subjectsQuantity;
    int _studentsQuantity;

    QTableWidget *_tableMarks;
    QTableWidget *_tableStudents;
    QComboBox *_comboBoxSubjects;

    bool isFileProcessing;

};

#endif // JOURNALMANAGER_H
