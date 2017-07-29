#include "journalmanager.h"
#include <fstream>
#include <QTextStream>
#include <QFile>
#include <QHeaderView>
#include <QMessageBox>

journalManager::journalManager()
{
    _studentsQuantity = 0;
    _subjectsQuantity = 0;
    _marksQuantity = 0;

    isFileProcessing = false;

}


bool journalManager::loadFile(const QString& fileName)
{

   QFile file(fileName);
   if(file.open(QIODevice::ReadOnly) )
   {
       _studentsQuantity = 0;
       _subjectsQuantity = 0;
       _marksQuantity = 0;

       isFileProcessing = true;

       _students.clear();
       _subjects.clear();
       //_marks.clear();

       QTextStream fin(&file);
       fin >> _studentsQuantity >> _subjectsQuantity >> _marksQuantity;
       for(int i = 0; i < _studentsQuantity; ++i)
       {
           QString tempSurname, tempName;
           fin >> tempSurname >> tempName;
           _students.push_back(tempSurname + " " + tempName);
       }

       fin.readLine();
       for(int i = 0; i < _subjectsQuantity; ++i)
       {
           _subjects.push_back(fin.readLine());
       }

       _marks.resize(_subjectsQuantity);
       for(int i = 0; i < _subjectsQuantity; ++i)
       {
           _marks[i].resize(_studentsQuantity);
           for(int j = 0; j < _studentsQuantity; ++j)
           {
               _marks[i][j].resize(_marksQuantity);
               for(int k = 0; k < _marksQuantity; ++k)
               {
                   fin >> _marks[i][j][k];
               }
           }
        }

       file.close();

       updateTableStudents();
       updateComboBoxSubjects();
       isFileProcessing = false;
       updateTableMarks(_comboBoxSubjects->currentIndex());
       return true;
   }
   return false;
}

bool journalManager::writeToFile(QString fileName) const

{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream fout(&file);
        if(fout.status() == QTextStream::Ok)
        {
            fout << _studentsQuantity << endl << _subjectsQuantity << endl << _marksQuantity << endl;
            for(int i = 0; i < _studentsQuantity; ++i)
            {
                fout << _students[i] << endl;
            }

            for(int i = 0; i < _subjectsQuantity; ++i)
            {
                fout << _subjects[i] << endl;
            }

            for(int i = 0; i < _subjectsQuantity; ++i)
            {
                for(int j = 0; j < _studentsQuantity; ++j)
                {
                    for(int k = 0; k < _marksQuantity; ++k)
                        fout << _marks[i][j][k] << " ";
                    fout << endl;
                }
            }
        }

        return true;
    }

    return false;
}
void journalManager::updateTableStudents()
{
    _tableStudents->verticalHeader()->setVisible(false);
    _tableStudents->horizontalHeader()->setVisible(false);
    _tableStudents->setColumnCount(1);
    _tableStudents->setRowCount(_studentsQuantity);
    _tableStudents->setColumnWidth(0, _tableStudents->geometry().width());

    for(int i = 0; i < _studentsQuantity; ++i)
    {
        _tableStudents->setItem(i, 0, new QTableWidgetItem(_students[i]) );
    }

}

void journalManager::updateComboBoxSubjects()
{
    _comboBoxSubjects->clear();
    for(int i = 0; i < _subjectsQuantity; ++i)
    {
        _comboBoxSubjects->addItem(_subjects[i]);
    }
}

void journalManager::addSubjectComboBox()
{
    _comboBoxSubjects->addItem(_subjects[_subjectsQuantity - 1]);
}

void journalManager::updateTableMarks(int subjectNumber)
{
    if(!isFileProcessing)
    {
        _tableMarks->horizontalHeader()->setVisible(false);
        _tableMarks->verticalHeader()->setVisible(false);

        _tableMarks->setColumnCount(_marksQuantity);
        _tableMarks->setRowCount(_studentsQuantity);
        int columnWidth = _tableMarks->geometry().width() / _marksQuantity - 1;
        for(int i = 0; i < _marksQuantity; ++i)
        {
            _tableMarks->setColumnWidth(i, columnWidth);
        }

        for(int i = 0; i < _studentsQuantity; ++i)
        {
            for(int j = 0; j < _marksQuantity; ++j)
            {
                QString temp = QString::number(_marks[subjectNumber][i][j]);
                _tableMarks->setItem(i, j, new QTableWidgetItem(temp) );
                _tableMarks->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}
