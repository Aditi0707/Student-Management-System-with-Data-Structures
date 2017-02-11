#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include<qlineedit.h>
#include<QScrollArea>
#include <string>
#include<QMessageBox>
using namespace std;


//bool loadData(Department *dep)
//{
//    fstream departmentFile;
//    fstream studentFile;
//    departmentFile.open("department.dat");
//    studentFile.open("student.dat");
//    if (departmentFile.is_open())
//    {
//        string Name = "";
//        int ID = 0;
//        string Location = "";
//        string School = "";
//        string Phone = "";
//        while (!departmentFile.eof())
//        {
//            departmentFile >> Name;
//            departmentFile >> ID;
//            departmentFile >> Location;
//            departmentFile >> School;
//            departmentFile >> Phone;
//            dep->addDepartment(Name, ID, Location, School,Phone);
//        }
//    }
//    else
//    {
//        cout << "Error openning file" << endl;
//    }
//    if (studentFile.is_open())
//    {
//        string Name = "";
//        string Fathername = "";
//        int Reg = 0;
//        string Class = "";
//        int depid = 0;
//        while (!studentFile.eof())
//        {
//            studentFile >> depid;
//            studentFile >> Reg;
//            studentFile >> Name;
//            studentFile >> Fathername;
//            studentFile >> Class;
//            if (!dep->addStudent(depid, Reg, Name, Fathername, Class))
//                return false;
//        }
//    }
//    return true;
//
//}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
//    loadData(&department);
	department.addDepartment("cs", 1, "h12", "seecs", "123");
	department.addStudent(1, 1, "Mohsin", "ansar", "c");
	department.addStudent(1, 2, "ammar", "ansar", "c");
	department.addStudent(1, 3, "waqas", "ansar", "c");
	department.addStudent(1, 4, "bilal", "ansar", "c");


}



MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_AddDepartmentButton_clicked()
{
    try
    {
        string name = ui->Regdepnamein->text().toStdString();
        int id = ui->Regdepidin->text().toInt();
        string location = ui->Regdeplocationin->text().toStdString();
        string school = ui->Regdepschoolin->text().toStdString();
        string phone = ui->Regdepphonein->text().toStdString();
        if(department.addDepartment(name,id,location,school,phone))
        {
            QMessageBox *message = new QMessageBox();
            message->setText("Success");
            message->show();
        }
        else
        {
            QMessageBox *message = new QMessageBox();
            message->setText("Error Occured");
            message->show();
        }
    }
    catch(exception ex)
    {
        QMessageBox *message = new QMessageBox();
        message->setText("Error Occured");
        message->show();
    }
}

void MainWindow::on_RegisterStudentButton_clicked()
{
    int depid = ui->regsid->text().toInt();
    int reg = ui->regSreg->text().toInt();
    string name = ui->regsname->text().toStdString();
    string fathername = ui->regsfather->text().toStdString();
    string Class = ui->regsclass->text().toStdString();
    try
    {
        if(department.addStudent(depid,reg,name,fathername,Class))
        {
            QMessageBox *message = new QMessageBox();
            message->setText("Success");
            message->show();
        }
        else
        {
            QMessageBox *message = new QMessageBox();
            message->setText("Error Occured");
            message->show();
        }
    }
    catch(exception ex)
    {
        QMessageBox *message = new QMessageBox();
        message->setText("Error Occured");
        message->show();
    }
}

void MainWindow::on_EditSsearchButton_clicked()
{
    int reg = ui->EditSreg->text().toInt();
    int dep = ui->editSdep->text().toInt();
    try
    {
        stack<string> studnt = department.SearchStudent(dep,reg);
        if(studnt.empty())
        {
            QMessageBox *message = new QMessageBox();
            message->setText("No student found");
            message->show();
        }
        else
        {
            QString temp = QString::fromStdString(studnt.top());
            ui->editSclass->setText(temp);
            studnt.pop();

            temp = QString::fromStdString(studnt.top());
            ui->editSfathername->setText(temp);
            studnt.pop();

            temp = QString::fromStdString(studnt.top());
            ui->EditSname->setText(temp);
            studnt.pop();
        }
    }
    catch(exception ex)
    {
        QMessageBox *message = new QMessageBox();
        message->setText("Error Occured");
        message->show();
    }
}

void MainWindow::on_editSsaveButton_clicked()
{
    string dep = ui->editSdep->text().toStdString();
    int reg = ui->EditSreg->text().toInt();
    string name = ui->EditSname->text().toStdString();
    string fathername = ui->editSfathername->text().toStdString();
    string Class = ui->editSclass->text().toStdString();
    department.editStudent(dep,reg,name,fathername,Class);
}

void MainWindow::on_editDepButton_clicked()
{
    stack<string> dep = department.SearchDepartment(ui->editDepText->text().toStdString());
    QString temp;

    if(!dep.empty())
    {
        ui->editDepName->setText(ui->editDepText->text());

        temp = QString::fromStdString(dep.top());
        ui->editDepId->setText(temp);
        dep.pop();

        temp = QString::fromStdString(dep.top());
        ui->editDepLocation->setText(temp);
        dep.pop();

        temp = QString::fromStdString(dep.top());
        ui->editDepSchool->setText(temp);
        dep.pop();

        temp = QString::fromStdString(dep.top());
        ui->editDepPhone->setText(temp);
        dep.pop();
    }
    else
    {
        QMessageBox *message = new QMessageBox();
        message->setText("No department found");
        message->show();
    }
}

void MainWindow::on_editDepSaveButton_clicked()
{
    string name = ui->editDepName->text().toStdString();
    int id = ui->editDepId->text().toInt();
    string location = ui->editDepLocation->text().toStdString();
    string school = ui->editDepSchool->text().toStdString();
    string phone = ui->editDepPhone->text().toStdString();
    department.editDepartment(name,id,location,school,phone);
}

void MainWindow::on_RemoveStudentButton_clicked()
{
    try
    {
        int id = ui->RemoveStudentRegText->text().toInt();
        int dep = ui->RemoveSDepartment->text().toInt();
        if(department.deleteStudent(dep,id))
        {
            QMessageBox *message = new QMessageBox();
            message->setText("Success");
            message->show();
        }
        else
        {
            QMessageBox *message = new QMessageBox();
            message->setText("Error occured");
            message->show();
        }
    }
    catch(exception ex)
    {
        QMessageBox *message = new QMessageBox();
        message->setText("Error occured");
        message->show();
    }
}

void MainWindow::on_RemoveStudentSearch_clicked()
{
    try
    {
        int id = ui->RemoveStudentRegText->text().toInt();
        int dep = ui->RemoveSDepartment->text().toInt();
        stack<string> result = department.SearchStudent(dep,id);
        if(!result.empty())
        {
            ui->RemoveStudentName->setText( QString::fromStdString(result.top()));
            result.pop();
            ui->RemoveStudentFName->setText( QString::fromStdString(result.top()));
            result.pop();
            ui->RemoveStudentClass->setText( QString::fromStdString(result.top()));
        }
        else
        {
            QMessageBox *message = new QMessageBox();
            message->setText("No student found");
            message->show();
        }
    }
    catch(exception ex)
    {
        QMessageBox *message = new QMessageBox();
        message->setText("Error occured");
        message->show();
    }
}

void MainWindow::on_RemoveDSearchButton_clicked()
{
    string name = ui->RemoveDnameText->text().toStdString();
    try
    {
        stack<string> result = department.SearchDepartment(name);
        if(!result.empty())
        {
            ui->RemoveDphone->setText(QString::fromStdString(result.top()));
            result.pop();
            ui->RemoveDschool->setText(QString::fromStdString(result.top()));
            result.pop();
            ui->RemoveDlocation->setText(QString::fromStdString(result.top()));
            result.pop();
            ui->RemoveDid->setText(QString::fromStdString(result.top()));
            result.pop();



        }
        QMessageBox *message = new QMessageBox();
        message->setText("No department found");
        message->show();
    }
    catch(exception ex)
    {
        QMessageBox *message = new QMessageBox();
        message->setText("Error occured");
        message->show();
    }
}

void MainWindow::on_RemoveDepartmentButton_clicked()
{
    try
    {
        string name = ui->RemoveDnameText->text().toStdString();
        int id = ui->RemoveDid->text().toInt();
        if(department.deleteDepartment(name,id))
        {
            QMessageBox *message = new QMessageBox();
            message->setText("Success");
            message->show();
        }
        else
        {
            QMessageBox *message = new QMessageBox();
            message->setText("Error occured");
            message->show();
        }
    }
    catch(exception ex)
    {
        QMessageBox *message = new QMessageBox();
        message->setText("Error occured");
        message->show();
    }
}

void MainWindow::on_SearchStudentButton_clicked()
{
    try
    {
        int id = ui->SearchStudentText->text().toInt();
        stack<string> result = department.SearchStudent(id);
        if(!result.empty())
        {
            ui->SearchSClass->setText(QString::fromStdString(result.top()));
            result.pop();

            ui->SearchSFname->setText(QString::fromStdString(result.top()));
            result.pop();

            ui->SearchSName->setText(QString::fromStdString(result.top()));
            result.pop();

        }
        else
        {
            QMessageBox *message = new QMessageBox();
            message->setText("No student found");
            message->show();
        }
    }
    catch(exception ex)
    {
        QMessageBox *message = new QMessageBox();
        message->setText("Error occured");
        message->show();
    }
}

void MainWindow::on_SearchByMarksButton_clicked()
{
    try
    {
        string dep = ui->SearchMDepText->text().toStdString();
        int reg = ui->SearchMreg->text().toInt();
        string Type = ui->SearchMtype->text().toStdString();
        string subject = ui->SearchMsubject->text().toStdString();
        stack<string> temp = department.SearchMarks(dep,reg,Type,subject);
        if(!temp.empty())
        {
            string output;
            output= "";
			ui->SearchByMarksList->clear();
            for(int i=0;i<temp.size()/3+1;i++)
            {
                output = temp.top() + "\t\t";
                temp.pop();
                output+=temp.top() + "\t\t";
                temp.pop();
                output+=temp.top() + "\t\t";
				temp.pop();
                QString label = QString::fromStdString(output);
                ui->SearchByMarksList->addItem(label);
            }

        }
    }
    catch(exception ex)
    {
        QMessageBox *message = new QMessageBox();
        message->setText("Error occured");
        message->show();
    }
}

void MainWindow::on_tab1_Button_clicked()
{
    ui->TabContainer->setCurrentIndex(0);
}

void MainWindow::on_tab2_Button_clicked()
{
    ui->TabContainer->setCurrentIndex(1);
}

void MainWindow::on_tab3_Button_clicked()
{
    ui->TabContainer->setCurrentIndex(2);
}

void MainWindow::on_tab4_Button_clicked()
{
    ui->TabContainer->setCurrentIndex(3);
}

void MainWindow::on_tab5_Button_clicked()
{
    ui->TabContainer->setCurrentIndex(4);
}

void MainWindow::on_tab6_Button_clicked()
{
    ui->TabContainer->setCurrentIndex(5);
}

void MainWindow::on_tab7_Button_clicked()
{
    ui->TabContainer->setCurrentIndex(6);
}

void MainWindow::on_tab8_Button_clicked()
{
    ui->TabContainer->setCurrentIndex(7);
}

void MainWindow::on_tab9_Button_clicked()
{
    ui->TabContainer->setCurrentIndex(8);
}

void MainWindow::on_AddMarksSeachButton_clicked()
{

	int n = deletetext.size();
	for (int i = 0; i < n; i++)
	{
		QLabel *temp = deletlabel.top();
		QLineEdit *temp2 = deletetext.top();
		deletlabel.pop();
		deletetext.pop();
		temp->setVisible(false);
		temp2->setVisible(false);
	}

    string dep = ui->AddMarksDep->text().toStdString();
    string Class = ui->AddMarksClass->text().toStdString();
    try
    {
        stack<string> Namelist = department.SearchByMarks(dep,Class);
        stack<int> RegList = department.SearchbyMarks(dep,Class);
        if(!Namelist.empty() && !RegList.empty())
        {
            QLineEdit *LineText;
			QLabel *Labels;
			LineText = new QLineEdit[RegList.size()];
			Labels = new QLabel[RegList.size()];

			int leng = RegList.size();
            for(int i=0;i<leng;i++)
            {
                string temp = to_string(RegList.top());
                LineText->setObjectName(QString::fromStdString(temp));
				Labels->setText(QString::fromStdString(Namelist.top()));

                ui->AddMarksList->addRow(Labels,LineText);

				Namelist.pop();
				RegList.pop();
                MarksTextList.enque(LineText);

				deletetext.push(LineText);
				deletlabel.push(Labels);

				LineText++;
				Labels++;
            }
			
        }
    }
    catch(exception ex)
    {
        QMessageBox *message = new QMessageBox();
        message->setText(ex.what());
        message->show();
    }
}




void MainWindow::on_AddMarksSaveButton_clicked()
{
	try
	{
		


		string dep = ui->AddMarksDep->text().toStdString();
		string Subject =  ui->AddMarksSubject->text().toStdString();
		int total = ui->AddMarksTotal->text().toInt();
		string MarksType = ui->AddMarksType->currentText().toStdString();
		int MarksNo = ui->AddMarksNo->currentText().toInt();

		int totals = MarksTextList.count;
		for(int i=0;i<totals;i++)
		{
		    QLineEdit *temp = MarksTextList.deque();
			int reg = temp->objectName().toInt();
			int obtained = temp->text().toInt();
			department.addMarks(dep, reg, total, obtained , MarksType, MarksNo, Subject);
		}
		QMessageBox *message = new QMessageBox();
		message->setText("Success");
		message->show();
		
	}
	catch (exception ex)
	{
		QMessageBox *message = new QMessageBox();
		message->setText("Error occured");
		message->show();
	}
}
