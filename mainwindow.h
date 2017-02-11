#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Source.cpp"
#include "marksqueue.cpp"
#include<qlabel.h>
#include<qline.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MarksQueue MarksTextList;
    Department department;
	stack<QLineEdit*> deletetext;
	stack<QLabel*> deletlabel;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_AddDepartmentButton_clicked();

    void on_RegisterStudentButton_clicked();

    void on_EditSsearchButton_clicked();

    void on_editSsaveButton_clicked();

    void on_editDepButton_clicked();

    void on_editDepSaveButton_clicked();

    void on_RemoveStudentButton_clicked();

    void on_RemoveStudentSearch_clicked();



    void on_RemoveDSearchButton_clicked();

    void on_RemoveDepartmentButton_clicked();

    void on_SearchStudentButton_clicked();

    void on_SearchByMarksButton_clicked();

    void on_tab1_Button_clicked();

    void on_tab2_Button_clicked();

    void on_tab3_Button_clicked();

    void on_tab4_Button_clicked();

    void on_tab5_Button_clicked();

    void on_tab6_Button_clicked();

    void on_tab7_Button_clicked();

    void on_tab8_Button_clicked();

    void on_tab9_Button_clicked();

    void on_AddMarksSeachButton_clicked();

    void on_AddMarksSaveButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
