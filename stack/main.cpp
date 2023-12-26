#include <iostream>
using namespace std;

struct ListNode
{ 
    int value;
    ListNode* next, * prev;

    ListNode() = default;
    ListNode(int val) : value(val), next(nullptr), prev(nullptr) {}
};

class CustomLinkedList
{
    ListNode* head, * tail;
    int size;

public:
    CustomLinkedList();
    CustomLinkedList(const CustomLinkedList&);
    ~CustomLinkedList();
    int getSize();
    ListNode* getNode(int);

    void clearAll();
    void removeNode(int position = 0);
    void insertNode(int position = 0);

    void addToTail(int val);
    void addToHead(int val);
    void displayList();
    void displayNode(int position);

    CustomLinkedList& operator=(const CustomLinkedList&);
    CustomLinkedList operator+(const CustomLinkedList&);
    bool operator==(const CustomLinkedList&);
    bool operator!=(const CustomLinkedList&);
    bool operator<=(const CustomLinkedList&);
    bool operator>=(const CustomLinkedList&);
    bool operator<(const CustomLinkedList&);
    bool operator>(const CustomLinkedList&);

    CustomLinkedList operator-();
};

CustomLinkedList::CustomLinkedList()
{
    head = tail = nullptr;
    size = 0;
}

CustomLinkedList::CustomLinkedList(const CustomLinkedList& list)
{
    head = tail = nullptr;
    size = 0;

    ListNode* temp = list.head;
    while (temp != nullptr) {
        this->addToTail(temp->value);
        temp = temp->next;
    }
}

CustomLinkedList::~CustomLinkedList()
{
    clearAll();
}

void CustomLinkedList::addToHead(int val)
{
    ListNode* temp = new ListNode(val);
    temp->prev = nullptr;
    temp->value = val;
    temp->next = head;

    if (head != nullptr) {
        head->prev = temp;
    }

    if (size == 0) {
        head = tail = temp;
    }
    else {
        head = temp;
    }

    size++;
}

void CustomLinkedList::addToTail(int val)
{
    ListNode* temp = new ListNode(val);
    temp->next = nullptr;
    temp->value = val;
    temp->prev = tail;

    if (tail != nullptr) {
        tail->next = temp;
    }

    if (size == 0) {
        head = tail = temp;
    }
    else {
        tail = temp;
    }

    size++;
}

void CustomLinkedList::insertNode(int position)
{
    int val;

    if (position == 0) {
        cout << "Set position: ";
        cin >> position;
    }

    if (position < 1 || position > size + 1) {
        cout << "Invalid position." << endl;
        return;
    }

    if (position == size + 1) {

        cout << "Enter new value: ";
        cin >> val;
        addToTail(val);
        return;
    }
    else if (position == 1) {

        cout << "Enter new value: ";
        cin >> val;
        addToHead(val);
        return;
    }

    int i = 1;
    ListNode* insertNode = head;

    while (i < position) {
        insertNode = insertNode->next;
        i++;
    }

    ListNode* prevInsertNode = insertNode->prev;
    ListNode* temp = new ListNode;
    cout << "Enter new value: ";
    cin >> temp->value;

    if (prevInsertNode != nullptr && size != 1)
        prevInsertNode->next = temp;

    temp->next = insertNode;
    temp->prev = prevInsertNode;
    insertNode->prev = temp;

    size++;
}

void CustomLinkedList::removeNode(int position)
{
    if (position == 0) {
        cout << "Set position: ";
        cin >> position;
    }
    if (position < 1 || position > size) {
        cout << "Invalid position" << endl;
        return;
    }

    int i = 1;
    ListNode* deleteNode = head;

    while (i < position)
    {
        deleteNode = deleteNode->next;
        i++;
    }

    ListNode* prevDeleteNode = deleteNode->prev;
    ListNode* nextDeleteNode = deleteNode->next;

    if (prevDeleteNode != nullptr && size != 1) {
        prevDeleteNode->next = nextDeleteNode;
    }

    if (nextDeleteNode != nullptr && size != 1) {
        nextDeleteNode->prev = prevDeleteNode;
    }

    if (position == 1) {
        head = nextDeleteNode;
    }

    if (position == size) {
        tail = prevDeleteNode;
    }
    delete deleteNode;
    size--;
}

void CustomLinkedList::displayNode(int position)
{
    if (position < 1 || position > size)
    {
        cout << "Invalid position" << endl;
        return;
    }

    ListNode* temp;
    if (position <= size / 2)
    {
        temp = head;
        int i = 1;

        while (i < position)
        {
            temp = temp->next;
            i++;
        }
    }
    else
    {
        temp = tail;
        int i = 1;

        while (i <= size - position)
        {
            temp = temp->prev;
            i++;
        }
    }
    cout << position << " element: ";
    cout << temp->value << endl;
}

void CustomLinkedList::displayList()
{
    if (size != 0)
    {
        ListNode* temp = head;
        cout << "[ ";
        while (temp->next != nullptr) {
            cout << temp->value << ", ";
            temp = temp->next;
        }

        cout << temp->value << " ]" << endl;
    }
}

void CustomLinkedList::clearAll()
{
    while (size != 0)
        removeNode(1);
}

int CustomLinkedList::getSize()
{
    return size;
}

ListNode* CustomLinkedList::getNode(int position)
{
    ListNode* temp = head;
    if (position < 1 || position > size) {
        cout << "Invalid position." << endl;
        return nullptr;
    }

    int i = 1;
    while (i < position && temp != nullptr) {
        temp = temp->next;
        i++;
    }

    if (temp == nullptr) {
        return nullptr;
    }
    else {
        return temp;
    }
}

CustomLinkedList& CustomLinkedList::operator=(const CustomLinkedList& list)
{
    if (this == &list) return *this;

    this->clearAll();

    ListNode* temp = list.head;

    while (temp != nullptr) {
        addToTail(temp->value);
        temp = temp->next;
    }

    return *this;
}

CustomLinkedList CustomLinkedList::operator+(const CustomLinkedList& list)
{
    CustomLinkedList result(*this);
    ListNode* temp = list.head;
    while (temp != nullptr) {
        result.addToTail(temp->value);
        temp = temp->next;
    }

    return result;
}

bool CustomLinkedList::operator==(const CustomLinkedList& list)
{
    if (size != list.size) return false;

    ListNode* t1, * t2;

    t1 = head;
    t2 = list.head;

    while (t1 != nullptr)
    {
        if (t1->value != t2->value) {
            return false;
        }
        t1 = t1->next;
        t2 = t2->next;
    }

    return true;
}

bool CustomLinkedList::operator!=(const CustomLinkedList& list)
{
    return !(*this == list);
}

bool CustomLinkedList::operator>=(const CustomLinkedList& list)
{
    if (size > list.size)return true;
    if (*this == list)return true;

    return false;
}

bool CustomLinkedList::operator<=(const CustomLinkedList& list)
{
    if (size < list.size) return true;
    if (*this == list) return true;

    return false;
}

bool CustomLinkedList::operator>(const CustomLinkedList& list)
{
    if (size > list.size) {
        return true;
    }

    return false;
}

bool CustomLinkedList::operator<(const CustomLinkedList& list)
{
    if (size < list.size)
        return true;

    return false;
}

CustomLinkedList CustomLinkedList::operator-()
{
    CustomLinkedList result;

    ListNode* temp = head;
    while (temp != nullptr)
    {
        result.addToHead(temp->value);
        temp = temp->next;
    }

    return result;
}

class CustomStack
{
    CustomLinkedList data;

public:
    CustomStack() {}

    void push(int value)
    {
        data.addToTail(value);
    }

    int pop()
    {
        if (!isEmpty())
        {
            ListNode* last = data.getNode(data.getSize());
            int value = last->value;
            data.removeNode(data.getSize());
            return value;
        }
        else
        {
            cout << "The stack is empty." << endl;
            return -1;
        }
    }

    bool isEmpty()
    {
        return data.getSize() == 0;
    }

    int getSize()
    {
        return data.getSize();
    }

    void display()
    {
        cout << "Stack: ";
        data.displayList();
    }
};

int main()
{
    CustomStack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    cout << "Pushed elements into stack." << endl;
    stack.display();

    int popped = stack.pop();
    cout << "Popped element: " << popped << endl;
    cout << "Stack size: " << stack.getSize() << endl;
    stack.display();

    int pushEl = 5;
    stack.push(pushEl);
    cout << "Pushed element " << pushEl << " into stack." << endl;
    stack.display();

    return 0;
}
