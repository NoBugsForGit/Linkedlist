#include<iostream>

class Linkedlist_int {
    /*
        存储整型数据的链表
    */
public:

    int value;//值
    int item;//索引
    int length;//链表长度
    Linkedlist_int* head;//整个链表的头指针
    Linkedlist_int* parent;//父节点的指针
    Linkedlist_int* next;//子节点的指针





    Linkedlist_int(int num, Linkedlist_int* par = nullptr) {
        value = num;
        parent = par;
        next = nullptr;

        if (parent == nullptr) {
            head = this;
            length = 1;
            item = 0;
        }

        else {
            parent->next = this;
            head = parent->head;
            length = parent->length;
            item = (parent->item) + 1;
        }

    }


private:

    void change_length(int delta) {
        int count = 0;
        for (Linkedlist_int* i = head; i != nullptr; i = i->next) {
            i->length += delta;
            i->item = count++;
        }
    }

    void change_head(Linkedlist_int* now_head) {
        for (Linkedlist_int* i = head; i != nullptr; i = i->next) {
            i->head = now_head;
        }
    }


public:

    Linkedlist_int* get_ptr(int target) {
        /*
            返回对应索引的节点指针
        */
        if (target < length) {
            Linkedlist_int* result = head;
            while (result->item != target) {
                result = result->next;
            }
            return result;
        }
        else { return nullptr; }
    }

    int get_value(int target) {
        /*
            返回对应索引的值
        */
        return (get_ptr(target)->value);
    }

    Linkedlist_int* append(int num) {
        /*
            向链表添加值，返回新值存储的地址指针
        */
        Linkedlist_int* temp=new Linkedlist_int(num,get_ptr(length-1));
        change_length(1);
        return temp;
    }


    void insert(int num, int target) {
        /*
            向链表中对应索引之后插入一个节点，并返回这个节点的指针
        */
        Linkedlist_int* position = get_ptr(target);
        Linkedlist_int* temp = position->next;
        Linkedlist_int* insert_node=new Linkedlist_int(num, position);
        insert_node->next = temp;
        if (temp != nullptr) {
            insert_node->next->parent = insert_node;
        }
        change_length(1);
    }


    Linkedlist_int* delete_ptr(Linkedlist_int* target,bool whether_not_from_delete_self=true) {
        if (target == this && whether_not_from_delete_self){
            return delete_self(); 
        }
        if (length == 1)
            { delete target; return 0; }
        if (target->parent == nullptr) {
            target->next->parent = nullptr;
            change_head(target->next);
        }
        else {
            target->parent->next = target->next;
            target->next->parent = target->parent;
        }
        change_length(-1);
        target->head = nullptr;//空置target的头指针，防止下一步调用析构函数出错
        delete target;
        return this;
    }

    Linkedlist_int* delete_item(int target) {
        return delete_ptr(get_ptr(target));
    }

    Linkedlist_int* delete_self() {
        /*
            删除自身，然后返回子节点的地址
        */
        Linkedlist_int* temp = this->next;
        delete_ptr(this,false);
        return temp;
    }

    void exchange_value(int item1, int item2) {
        Linkedlist_int* ptr1 = get_ptr(item1);
        Linkedlist_int* ptr2 = get_ptr(item2);
        int temp = ptr1->value;
        ptr1->value = ptr2->value;
        ptr2->value = temp;
    }

    int print(const char* separator="\t") {
        /*
            按照传入的分隔符，按顺序输出所有节点的值，并返回链表长度
        */
        Linkedlist_int* temp = head;
        while (temp != nullptr) {
            std::cout << temp->value <<separator ;
            temp = temp->next;
        }
        std::cout << "\n";
        delete temp;
        return length;
    }


    ~Linkedlist_int() {
        Linkedlist_int* temp = head;
        while (temp != nullptr) {
            Linkedlist_int* next = temp->next;
            delete temp;
            temp = next;
        }
    }


};

inline Linkedlist_int* Create_Linkedlist_int(int* arr,int length) {
    Linkedlist_int* head = new Linkedlist_int(arr[0]);
    for (int i = 1; i < length; i++) {
        head->append(arr[i]);
    }
    return head;
}