// constructor
DoublyLinkedList() { head = nullptr; tail = nullptr; }

~DoublyLinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void push_back(int value) {
    Node* newNode = new Node(value);
    if (!tail)  // if there's no tail, the list is empty
        head = tail = newNode;
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void push_front(int value) {
    Node* newNode = new Node(value);
    if (!head)  // if there's no head, the list is empty
        head = tail = newNode;
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void insert_after(int value, int position) {
    if (position < 0) {
        cout << "Position must be >= 0." << endl;
        return;
    }

    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
        return;
    }

    Node* temp = head;
    for (int i = 0; i < position && temp; ++i)
        temp = temp->next;

    if (!temp) {
        cout << "Position exceeds list size. Node not inserted.\n";
        delete newNode;
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next)
        temp->next->prev = newNode;
    else
        tail = newNode; // Inserting at the end
    temp->next = newNode;
}

void delete_val(int value) {
    if (!head) return; // Empty list

    Node* temp = head;
    while (temp && temp->data != value)
        temp = temp->next;

    if (!temp) return; // Value not found

    if (temp->prev) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next; // Deleting the head
    }

    if (temp->next) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev; // Deleting the tail
    }

    delete temp;
}

int delete_pos(size_t pos);
int pop_front();
int pop_back();

void print() {
    Node* current = head;
    if (!current) return;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void print_reverse() {
    Node* current = tail;
    if (!current) return;
    while (current) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
}