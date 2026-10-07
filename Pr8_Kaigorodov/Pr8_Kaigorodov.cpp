// Pr8_Kaigorodov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Task {
    char title[60];
    int priority;
    bool completed;
};

struct Node {
    Task data;
    Node* next;
    Node* prev;
};

struct List {
    Node* head;
    Node* tail;
};

void initList(List& lst) {
    lst.head = nullptr;
    lst.tail = nullptr;
}

void push_front(List& lst, Task t) {
    Node* node = new Node;
    node->data = t;
    node->prev = nullptr;
    node->next = lst.head;

    if (lst.head != nullptr)
        lst.head->prev = node;
    else
        lst.tail = node;

    lst.head = node;
}

void push_back(List& lst, Task t) {
    Node* node = new Node;
    node->data = t;
    node->next = nullptr;
    node->prev = lst.tail;

    if (lst.tail != nullptr)
        lst.tail->next = node;
    else
        lst.head = node;

    lst.tail = node;
}

void pop_front(List& lst) {
    if (lst.head == nullptr) return;

    Node* temp = lst.head;
    lst.head = lst.head->next;

    if (lst.head != nullptr)
        lst.head->prev = nullptr;
    else
        lst.tail = nullptr;

    delete temp;
}

void pop_back(List& lst) {
    if (lst.tail == nullptr) return;

    Node* temp = lst.tail;
    lst.tail = lst.tail->prev;

    if (lst.tail != nullptr)
        lst.tail->next = nullptr;
    else
        lst.head = nullptr;

    delete temp;
}

void display_forward(List& lst) {
    if (lst.head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    cout << "--- Список (начало -> конец) ---\n";
    Node* cur = lst.head;
    int i = 1;
    while (cur != nullptr) {
        cout << i << ") \"" << cur->data.title << "\""
            << " | приоритет: " << cur->data.priority
            << " | " << (cur->data.completed ? "выполнена" : "не выполнена")
            << "\n";
        cur = cur->next;
        i++;
    }
}

void display_backward(List& lst) {
    if (lst.tail == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    cout << "--- Список (конец -> начало) ---\n";
    Node* cur = lst.tail;
    int i = 1;
    while (cur != nullptr) {
        cout << i << ") \"" << cur->data.title << "\""
            << " | приоритет: " << cur->data.priority
            << " | " << (cur->data.completed ? "выполнена" : "не выполнена")
            << "\n";
        cur = cur->prev;
        i++;
    }
}

Node* findByName(List& lst, const char* name) {
    Node* cur = lst.head;
    while (cur != nullptr) {
        if (strcmp(cur->data.title, name) == 0)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

void removeNode(List& lst, Node* node) {
    if (node == nullptr) return;

    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        lst.head = node->next;

    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        lst.tail = node->prev;

    delete node;
}

bool removeByTitle(List& lst, const char* name) {
    Node* node = findByName(lst, name);
    if (node == nullptr) return false;
    removeNode(lst, node);
    return true;
}

void clear(List& lst) {
    Node* cur = lst.head;
    while (cur != nullptr) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    lst.head = nullptr;
    lst.tail = nullptr;
}

Node* findMaxPriorityIncomplete(List& lst) {
    Node* best = nullptr;
    Node* cur = lst.head;
    while (cur != nullptr) {
        if (cur->data.completed == false) {
            if (best == nullptr || cur->data.priority > best->data.priority)
                best = cur;
        }
        cur = cur->next;
    }
    return best;
}

int removeCompleted(List& lst) {
    int removed = 0;
    Node* cur = lst.head;
    while (cur != nullptr) {
        Node* next = cur->next;   
        if (cur->data.completed == true) {
            removeNode(lst, cur);
            removed++;
        }
        cur = next;
    }
    return removed;
}

bool moveToEnd(List& lst, const char* name) {
    Node* node = findByName(lst, name);
    if (node == nullptr) return false;
    if (node == lst.tail) return true;   

    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        lst.head = node->next;

    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        lst.tail = node->prev;

    node->prev = lst.tail;
    node->next = nullptr;

    if (lst.tail != nullptr)
        lst.tail->next = node;

    lst.tail = node;

    if (lst.head == nullptr)
        lst.head = node;

    return true;
}

Task inputTask() {
    Task t;

    cout << "Введите название задачи: ";
    cin.ignore(10000, '\n');
    cin.getline(t.title, 60);

    cout << "Введите приоритет (целое число): ";
    cin >> t.priority;

    int comp;
    cout << "Задача выполнена? (1 - да, 0 - нет): ";
    cin >> comp;
    t.completed = (comp == 1);

    return t;
}

void printMenu() {
    cout << "\n========== МЕНЮ ==========\n";
    cout << "1.  Добавить задачу в начало\n";
    cout << "2.  Добавить задачу в конец\n";
    cout << "3.  Удалить первую задачу\n";
    cout << "4.  Удалить последнюю задачу\n";
    cout << "5.  Вывести список (начало -> конец)\n";
    cout << "6.  Вывести список (конец -> начало)\n";
    cout << "7.  Найти задачу по названию\n";
    cout << "8.  Удалить задачу по названию\n";
    cout << "9.  Найти невыполненную задачу с максимальным приоритетом\n";
    cout << "10. Удалить все выполненные задачи\n";
    cout << "11. Переместить задачу в конец списка\n";
    cout << "12. Очистить список\n";
    cout << "0.  Выход\n";
    cout << "Выберите пункт: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    List lst;
    initList(lst);

    int choice;

    do {
        printMenu();
        cin >> choice;

        if (choice == 1) {
            Task t = inputTask();
            push_front(lst, t);
            cout << "Задача добавлена в начало.\n";
        }
        else if (choice == 2) {
            Task t = inputTask();
            push_back(lst, t);
            cout << "Задача добавлена в конец.\n";
        }
        else if (choice == 3) {
            pop_front(lst);
            cout << "Первая задача удалена (если список был не пуст).\n";
        }
        else if (choice == 4) {
            pop_back(lst);
            cout << "Последняя задача удалена (если список был не пуст).\n";
        }
        else if (choice == 5) {
            display_forward(lst);
        }
        else if (choice == 6) {
            display_backward(lst);
        }
        else if (choice == 7) {
            char name[60];
            cout << "Введите название для поиска: ";
            cin.ignore(10000, '\n');
            cin.getline(name, 60);

            Node* found = findByName(lst, name);
            if (found != nullptr) {
                cout << "Найдено: \"" << found->data.title << "\""
                    << " | приоритет: " << found->data.priority
                    << " | " << (found->data.completed ? "выполнена" : "не выполнена")
                    << "\n";
            }
            else {
                cout << "Задача не найдена.\n";
            }
        }
        else if (choice == 9) {
            Node* best = findMaxPriorityIncomplete(lst);
            if (best != nullptr) {
                cout << "Невыполненная задача с максимальным приоритетом:\n";
                cout << "  \"" << best->data.title << "\""
                    << " | приоритет: " << best->data.priority << "\n";
            }
            else {
                cout << "Невыполненных задач нет.\n";
            }
        }
        else if (choice == 10) {
            int removed = removeCompleted(lst);
            cout << "Удалено выполненных задач: " << removed << "\n";
        }
        else if (choice == 11) {
            char name[60];
            cout << "Введите название задачи для перемещения в конец: ";
            cin.ignore(10000, '\n');
            cin.getline(name, 60);

            if (moveToEnd(lst, name))
                cout << "Задача перемещена в конец.\n";
            else
                cout << "Задача не найдена.\n";
        }
        else if (choice == 12) {
            clear(lst);
            cout << "Список очищен.\n";
        }
        else if (choice == 0) {
            cout << "Выход.\n";
        }
        else {
            cout << "Неверный пункт меню.\n";
        }
    } while (choice != 0);

    clear(lst);

    return 0;
}