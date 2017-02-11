#include<iostream>
#include<string>
#include<fstream>
#include<stack>
using namespace std;




class Marks
{
private:
	struct node
	{
		float total;
		float obtained;
        string TypeOf;
		int number;
		string subject;
		struct node *next;
		node()
		{
			total = 0;
			obtained = 0;
            TypeOf = "";
			number = 0;
			next = NULL;
			subject = "";
		}
        node(float Total, float Obtained, string Typeof, int Number,string Subject)
		{
			total = Total;
			obtained = Obtained;
            TypeOf = Typeof;
			number = Number;
			subject = Subject;
			next = NULL;
		}
	};
	node *head;
public:
	int reg;
	string department;
	Marks()
	{
		head = NULL;
		reg = 0;
		department = "";
	}
	Marks(int Reg, string Department)
	{
		reg = Reg;
		department = Department;
	}
	void push(float Total, float Obtained, string Typeof, int Number,string Subject)
	{
		if (!head)
			head = new node(Total, Obtained, Typeof, Number,Subject);
		else
		{
			node *itr = head, *NewNode = new node(Total, Obtained, Typeof, Number,Subject);
			head = NewNode;
			NewNode->next = itr;
		}
	}
	node pop()
	{
		node temp;
		if (!head)
			return temp;
		node *itr = head;
		temp.total = head->total;
		temp.obtained = head->obtained;
        temp.TypeOf = head->TypeOf;
		temp.number = head->number;
		temp.subject = head->subject;
		head = head->next;
		delete itr;
		return temp;
	}
    stack<string> getMarks(string typeOf,string Subject)
    {
        stack<string> temp;
                if (!head)
                    return temp;
                else
                {
                    node *itr = head;
                    while (itr)
                    {
                        if (itr->TypeOf == typeOf && itr->subject == Subject)
                        {
                            temp.push(to_string(itr->total));
                            temp.push(to_string(itr->obtained));
                            temp.push(to_string(itr->number));
                        }
                        itr = itr->next;
                    }
                    return temp;
                }
    }

    ~Marks()
	{
		node *temp = head;
		while (head)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}
};

class student
{
private:
	string department;
	int count;
	struct node
	{
		struct node *parent;
		struct node *left;
		struct node *right;
		string name;
		string fathername;
		int reg;
		string Class;
		Marks marks;
		node(string Name,string fatherName,string Cls,int Reg)
		{
			name = Name;
			fathername = fatherName;
			Class = Cls;
			reg = Reg;
			parent = NULL;
			left = NULL;
			right = NULL;
		}
	};
	node *root;
	void insert(node *Parent,node *itr, node *NewNode)
	{
		if (itr == NULL)
		{
			return;
		}
		else
		{
			if (NewNode->reg > itr->reg)
			{
				if (itr->right != NULL)
				{
					insert(itr, itr->right, NewNode);
					return;
				}
				itr->right = NewNode;
				NewNode->parent = itr;
				return;
			}
			else if (NewNode->reg < itr->reg)
			{
				if (itr->left != NULL)
				{
					insert(itr, itr->left, NewNode);
					return;
				}
				itr->left = NewNode;
				NewNode->parent = itr;
				return;
			}
			else
			{
				return;
			}
		}
		return;
	}
	bool deleteNode(node *parent,node *itr,int Reg)
	{
		if (!itr)
			return false;
		else if (Reg < itr->reg)
			return deleteNode(itr,itr->left, Reg);
		else if (Reg > itr->reg)
			return deleteNode(itr,itr->right, Reg);
		else if (Reg == itr->reg)
		{
			if (!itr->left && !itr->right)
			{
				delete itr;
				if (parent && parent->left == itr) parent->left = NULL;
				else if (parent && parent->right == itr) parent->right = NULL;
				return true;
			}

			else if (!itr->left && itr->right)
			{
				if (parent && parent->left == itr)
				{
					parent->left = itr->right;
				}
				else if (parent && parent->right == itr)
				{ 
					parent->right = itr->right; 
				}
				return true;
			}

			else if (itr->left && !itr->right)
			{
				if (parent && parent->left == itr)
				{
					node *tem = parent->left;
					parent->left = itr->left;
					delete tem;
				}
				else if (parent && parent->right == itr) 
				{
					node *tem = parent->right;
					parent->right = itr->left;
					delete tem;
				}
				return true;
			}
			else
			{
				node *predecessor = itr->right;
				node *previous = NULL;
				while (predecessor && predecessor->left)
				{
					previous = predecessor;
					predecessor = predecessor->left;
				}
				itr->reg = predecessor->reg;
				itr->Class = predecessor->Class;
				itr->fathername = predecessor->fathername;
				itr->marks = predecessor->marks;
				itr->name = predecessor->name;
				if (previous)
					deleteNode(previous, predecessor,predecessor->reg);
				else
				{
					node *temp = itr->right;
					if (itr->right->right)
						itr->right = itr->right->right;
					else
						itr->right = NULL;
					delete temp;
				}
			}
			return true;
		}
		else return false;
	}
	void searchByClass(stack<string> *list, node *itr,string Class)
	{
		if (!itr)
			return;
		if (itr->Class == Class)
			list->push(itr->name);
		searchByClass(list,itr->left,Class);
		searchByClass(list,itr->right,Class);
	}
    void searchbyClass(stack<int> *list, node *itr, string Class)
        {
            if (!itr)
                return;
            if (itr->Class == Class)
                list->push(itr->reg);
            searchbyClass(list, itr->left, Class);
            searchbyClass(list, itr->right, Class);
        }

    void destroy(node *itr)
	{
		if (!itr)
			return;
		destroy(itr->left);
		destroy(itr->right);
		delete itr;
		return;
	}
public:
	student()
	{
		count = 0;
		root = NULL;
		department = "";
	}
	/*node *predecessor(node *itr)
	{
		if (!itr)
			return NULL;
		itr = itr->right;
		while (itr && itr->left)
		{
			itr = itr->left;
		}
		return itr;
	}*/
	bool Delete(int Reg)
	{
		if (deleteNode(NULL, root, Reg))
		{
			count--;
			return true;
		}
		
		return false;
	}
	bool add(string Name, string fatherName, string Cls,int Reg)
	{
		if (root == NULL)
		{
			root = new node(Name, fatherName, Cls, Reg);
			count++;
			return true;
		}
		else
		{
			node *NewNode = new node(Name, fatherName, Cls,Reg);
			NewNode->marks.department = department;
			NewNode->marks.reg = Reg;
			insert(NULL,root, NewNode);
			count++;
			return true;
		}
		return false;
	}
	bool edit(int Reg, string Name, string fatherName, string Cls)
	{
		node *itr = root;
		while (itr && itr->reg != Reg)
		{
			if (Reg < itr->reg)
				itr = itr->left;
			else if (Reg>itr->reg)
				itr = itr->right;
		}
		if (!itr)
			return false;
		itr->name = Name;
		itr->fathername = fatherName;
		itr->Class = Cls;
        return true;
	}
	void addMarks(int Reg, float Total, float Obtained, string Typeof, int Number,string Subject)
	{
		node *itr = root;
		while (itr && itr->reg != Reg)
		{
			if (Reg < itr->reg)
				itr = itr->left;
			else if (Reg>itr->reg)
				itr = itr->right;
		}
		if (!itr)
			return;
		itr->marks.push(Total, Obtained, Typeof, Number,Subject);
	}
	stack<string> searchStudent(int Reg)
	{
		stack<string> temp;
		node *itr = root;
		while (itr && itr->reg != Reg)
		{
			if (Reg < itr->reg)
				itr = itr->left;
			else if (Reg > itr->reg)
				itr = itr->right;
		}
		if (!itr)
			return temp;
		temp.push( itr->name);
		temp.push( itr->fathername);
		temp.push( itr->Class);
		return temp;
	}
	stack<string> searchByClass(string Class)
	{
		stack<string> list;
		searchByClass(&list, root,Class);
		return list;
	}
   stack<int> searchbyClass(string Class)
        {
            stack<int> list;
            searchbyClass(&list, root, Class);
            return list;
        }
    stack<string> getMarks(int Reg, string typeOf, string Subject)
    {
        stack<string> temp;
        node *itr = root;
        while (itr && itr->reg != Reg)
        {
            if (Reg < itr->reg)
                itr = itr->left;
            else if (Reg > itr->reg)
                itr = itr->right;
        }
        if (!itr)
            return temp;
        temp = itr->marks.getMarks(typeOf, Subject);
        return temp;
    }

    ~student()
	{
		destroy(root);
	}

};


class Department
{
private:
	struct  node
	{
		student Student;
		string name;
		int id;
		string location;
		string school;
		string phone;
		struct node *next;
		struct node *previous;
		node()
		{
			name = "";
			id = 0;
			location = "";
			school = "";
			next = NULL;
			previous = NULL;
		}
		node(string Name, int ID, string Location, string School,string Phone)
		{
			name = Name;
			id = ID;
			location = Location;
			school = School;
			phone = Phone;
			next = NULL;
			previous = NULL;
		}
	};
	node *head;
public:
	bool addDepartment(string Name, int ID, string Location, string School,string Phone)
	{
		if (!head)
		{
			head = new node(Name, ID, Location, School,Phone);
			return true;
		}
		else
		{
			node *itr = head;
			while (itr->next)
			{
				itr = itr->next;
			}
			itr->next = new node(Name, ID, Location, School,Phone);
			itr->next->previous = itr;
			return true;
		}
		return false;
	}
	bool deleteDepartment(string Name, int ID)
	{
		if (!head)
			return false;
		node *itr = head, *previous = NULL;
		while (itr && itr->id != ID && Name != itr->name)
		{
			itr = itr->next;
		}
		if (!itr)
			return false;
		if (previous)
		{
			previous->next = itr->next;
			delete itr;
		}
		else
		{
			head = head->next;
			delete itr;
		}
        return true;
	}
	bool addStudent(int depid, int Reg, string Name, string Fathername, string Class)
	{
		if (!head)
			return false;
		node *itr = head;
		while (itr &&  itr->id != depid)
		{
			itr = itr->next;
		}
		if (!itr)
			return false;
		if (!itr->Student.add(Name, Fathername, Class, Reg))
			return false;
		return true;
	}
	bool deleteStudent(int depid, int Reg)
	{
		if (!head)
			return false;
		node *itr = head;
		while (itr && itr->id != depid)
		{
			itr = itr->next;
		}
		if (!itr)
			return false;
		return itr->Student.Delete(Reg);
	}
	bool addMarks(string dep, int reg, float Total, float Obtained, string Typeof, int Number,string Subject)
	{
		node *itr = head;
		while (itr && itr->name != dep)
		{
			itr = itr->next;
		}
		if (!itr)
			return false;
		itr->Student.addMarks(reg, Total, Obtained, Typeof, Number,Subject);
        return true;
	}
	bool editStudent(string dep, int Reg, string Name, string fatherName, string Cls)
	{
		node *itr = head;
		while (itr && itr->name != dep)
		{
			itr = itr->next;
		}
		if (!itr)
			return false;
		itr->Student.edit(Reg, Name, fatherName, Cls);
        return true;
	}
	bool editDepartment(string Name, int ID, string Location, string School, string Phone)
	{
		node *itr = head;
		while (itr && itr->id != ID)
		{
			itr = itr->next;
		}
		if (!itr)
			return false;
		itr->name = Name;
		itr->location = Location;
		itr->phone = Phone;
		itr->school = School;
        return true;
	}

    stack<string> SearchDepartment(string dep)
    {
        stack<string> temp;
        if(!head)
            return temp;
        node *itr = head;
        while(itr && itr->name!=dep)
            itr = itr->next;
        if(!itr)
            return temp;
        else
        {
            temp.push(to_string(itr->id));
            temp.push(itr->location);
            temp.push(itr->school);
            temp.push(itr->phone);
        }
        return temp;
    }

    stack<string> SearchStudent(int depid, int reg)
	{
		stack<string> temp;
		node *itr = head;
        while (itr && itr->id != depid)
		{
			itr = itr->next;
		}
		if (!itr)
			return temp;
		temp = itr->Student.searchStudent(reg);
		return temp;
	}

    stack<string> SearchStudent(int reg)
    {
        stack<string> temp;
        node *itr = head;
        while (itr && itr->next)
        {
            temp = itr->Student.searchStudent(reg);
            if(!temp.empty())
                return temp;
            itr = itr->next;
        }
        return temp;
    }


    stack<string> SearchByMarks(string dep,string Class)
	{
		stack<string> temp;
		node *itr = head;
		while (itr && itr->name != dep)
		{
			itr = itr->next;
		}
		if (!itr)
			return temp;
		temp = itr->Student.searchByClass(Class);
		return temp;
	}

    stack<int> SearchbyMarks(string dep, string Class)
        {
            stack<int> temp;
            node *itr = head;
            while (itr && itr->name != dep)
            {
                itr = itr->next;
            }
            if (!itr)
                return temp;
            temp = itr->Student.searchbyClass(Class);
            return temp;
        }

    stack<string> SearchMarks(string dep, int Reg, string typeOf, string Subject)
    {
        stack<string> temp;
        node *itr = head;
        while (itr && itr->name != dep)
        {
            itr = itr->next;
        }
        if (!itr)
            return temp;
        temp = itr->Student.getMarks(Reg, typeOf, Subject);
        return temp;
    }


    Department()
	{
		head = NULL;
		
	}
	~Department()
	{
		node *itr;
		while (head)
		{
			itr = head;
			head = head->next;
			delete itr;
		}
	}
};


/*bool loadData(Department *dep)
{
	fstream departmentFile;
	fstream studentFile;
	departmentFile.open("department.dat");
	studentFile.open("student.dat");
	if (departmentFile.is_open())
	{
		string Name = "";
		int ID = 0;
		string Location = "";
		string School = "";
		string Phone = "";
		while (!departmentFile.eof())
		{
			departmentFile >> Name;
			departmentFile >> ID;
			departmentFile >> Location;
			departmentFile >> School;
			departmentFile >> Phone;
			dep->addDepartment(Name, ID, Location, School,Phone);
		}
	}
	else
	{
		cout << "Error openning file" << endl;
	}
	if (studentFile.is_open())
	{
		string Name = "";
		string Fathername = "";
		int Reg = 0;
		string Class = "";
		int depid = 0;
		while (!studentFile.eof())
		{
			studentFile >> depid;
			studentFile >> Reg;
			studentFile >> Name;
			studentFile >> Fathername;
			studentFile >> Class;
			if (!dep->addStudent(depid, Reg, Name, Fathername, Class))
				return false;
		}
	}
	return true;

}*/





