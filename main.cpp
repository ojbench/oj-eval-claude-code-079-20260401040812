#include <iostream>
#include <cstdio>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

struct LinkedList {
    Node* head;
    int length;

    LinkedList() : head(nullptr), length(0) {}

    void initialize() {
        int n;
        scanf("%d", &n);
        int *a = new int[n];
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);

        // Build linked list from array
        if (n > 0) {
            head = new Node(a[0]);
            Node* current = head;
            for (int i = 1; i < n; i++) {
                current->next = new Node(a[i]);
                current = current->next;
            }
            length = n;
        }

        delete[] a;
    }

    void insert(int i, int x) {
        // Insert x after the i-th node (1-indexed)
        if (i == 0) {
            // Insert at the beginning
            Node* newNode = new Node(x);
            newNode->next = head;
            head = newNode;
            length++;
            return;
        }

        Node* current = head;
        for (int j = 1; j < i && current != nullptr; j++) {
            current = current->next;
        }

        if (current != nullptr) {
            Node* newNode = new Node(x);
            newNode->next = current->next;
            current->next = newNode;
            length++;
        }
    }

    void erase(int i) {
        // Delete the i-th node (1-indexed)
        if (i == 1) {
            // Delete the first node
            if (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
                length--;
            }
            return;
        }

        Node* current = head;
        for (int j = 1; j < i - 1 && current != nullptr; j++) {
            current = current->next;
        }

        if (current != nullptr && current->next != nullptr) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            length--;
        }
    }

    void swap() {
        // Swap odd and even positions (1-indexed)
        // 1 <-> 2, 3 <-> 4, 5 <-> 6, ...
        if (head == nullptr || head->next == nullptr) return;

        Node* prev = nullptr;
        Node* first = head;
        Node* second = head->next;
        head = second; // New head is the second node

        while (first != nullptr && second != nullptr) {
            Node* nextPair = second->next;

            // Swap first and second
            second->next = first;
            first->next = nextPair;

            if (prev != nullptr) {
                prev->next = second;
            }

            prev = first;

            // Move to next pair
            if (nextPair != nullptr) {
                first = nextPair;
                second = nextPair->next;
            } else {
                break;
            }
        }
    }

    void moveback(int i, int x) {
        // Move the first i nodes backward by x positions
        // Example: 1->2->3->4->5, moveback(2, 2) => 3->4->1->2->5
        if (i == 0 || x == 0 || head == nullptr) return;

        // Find the i-th node and the node before it
        Node* current = head;
        Node* ithNode = nullptr;
        for (int j = 1; j <= i && current != nullptr; j++) {
            if (j == i) {
                ithNode = current;
            }
            current = current->next;
        }

        if (ithNode == nullptr) return;

        // Find the (i+x)-th node
        Node* targetPrev = head;
        for (int j = 1; j < i + x && targetPrev != nullptr; j++) {
            targetPrev = targetPrev->next;
        }

        if (targetPrev == nullptr) return;

        // Extract first i nodes
        Node* firstSegment = head;
        Node* afterFirstSegment = ithNode->next;
        ithNode->next = targetPrev->next;

        // Update head to point to the node after first i nodes
        head = afterFirstSegment;

        // Connect the segment that was moved
        targetPrev->next = firstSegment;
    }

    int query(int i) {
        // Query the i-th node (1-indexed)
        Node* current = head;
        for (int j = 1; j < i && current != nullptr; j++) {
            current = current->next;
        }

        if (current != nullptr) {
            return current->data;
        }
        return -1; // Should not happen with valid input
    }

    void printAll() {
        Node* current = head;
        bool first = true;
        while (current != nullptr) {
            if (!first) printf(" ");
            printf("%d", current->data);
            first = false;
            current = current->next;
        }
        printf("\n");
    }

    void ClearMemory() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        length = 0;
    }
};

int main() {
    LinkedList List;
    int m, op, i, x;
    List.initialize();
    scanf("%d", &m);
    while(m--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &i, &x);
            List.insert(i, x);
        }
        else if(op == 2) {
            scanf("%d", &i);
            List.erase(i);
        }
        else if(op == 3) {
            List.swap();
        }
        else if(op == 4) {
            scanf("%d%d",&i, &x);
            List.moveback(i, x);
        }
        else if(op == 5) {
            scanf("%d", &i);
            printf("%d\n", List.query(i));
        }
        else if(op == 6) {
            List.printAll();
        }
    }
    List.ClearMemory();
    return 0;
}
