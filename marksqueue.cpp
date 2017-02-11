#include<iostream>
#include<string>
#include<QLineEdit>
using namespace std;
class MarksQueue
{
public:
    int count;
    struct node
    {
        QLineEdit *text;
        node *next;
        node()
        {
            next = NULL;
            text = NULL;
        }
        node(QLineEdit *Text)
        {
           text = Text;
		   next = NULL;
        }
    };
    node *head;
    node *tail;
    MarksQueue()
    {
        count =0;
        head = NULL;
        tail = NULL;
    }

    void enque(QLineEdit *Text)
    {
        if(!head)
        {
            head = new node(Text);
            tail = head;
            count++;
            return;
        }
        else
        {
            tail->next = new node(Text);
            tail = tail->next;
            count++;
        }
    }

    QLineEdit* deque()
    {
        if(!head)
            return NULL;
        else
        {
            node *itr = head;
            head = head->next;
            count--;
            return itr->text;
        }
    }
    QLineEdit* top()
    {
        if(!head)
            return NULL;
        else
        {
            return head->text;
        }
    }

};

