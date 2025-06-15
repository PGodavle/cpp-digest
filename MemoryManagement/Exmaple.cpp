#include <iostream>
#include <memory>

 /*Explanation of the Example
Smart Pointers: The Node struct uses std::unique_ptr for the next pointer, ensuring automatic memory cleanup when nodes are removed or the list is destroyed.
Linked List: The insert function dynamically creates nodes and manages ownership using std::move to transfer unique_ptr ownership.
Raw Pointers: The main function includes a raw pointer example to contrast with smart pointers, showing manual allocation and deallocation.
Safety: Using unique_ptr eliminates the need for manual delete calls and prevents memory leaks.
  */
struct Node {
    int data;
    std::unique_ptr<Node> next;  // Use unique_ptr for automatic cleanup
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
    std::unique_ptr<Node> head;

public:
    void insert(int val) {
        auto newNode = std::make_unique<Node>(val);
        newNode->next = std::move(head);  // Transfer ownership
        head = std::move(newNode);
    }

    void print() {
        Node* current = head.get();  // Get raw pointer for traversal
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next.get();
        }
        std::cout << "nullptr" << std::endl;
    }
};

int main() {
    LinkedList list;
    list.insert(3);
    list.insert(2);
    list.insert(1);
    list.print();  // Outputs: 1 -> 2 -> 3 -> nullptr

    // Manual memory management example (not recommended)
    int* rawPtr = new int(42);
    std::cout << "Raw pointer value: " << *rawPtr << std::endl;
    delete rawPtr;  // Must manually free memory
    rawPtr = nullptr;

    return 0;
}
