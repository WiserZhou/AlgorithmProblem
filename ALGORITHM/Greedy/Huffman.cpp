#include <iostream>
#include <queue>
#include <vector>
#include <utility> // for std::pair

struct Node
{
    int freq;
    char c;
    Node *left = nullptr;
    Node *right = nullptr;

    // Custom comparator for priority_queue (as C++ doesn't have direct lt overload in struct)
    struct Compare
    {
        bool operator()(Node *l, Node *r)
        {
            return l->freq > r->freq; // Note the inversion for max heap behavior
        }
    };
};

// Function to create a new node with given frequency and character
Node *newNode(int freq, char c)
{
    Node *node = new Node();
    node->freq = freq;
    node->c = c;
    return node;
}

// Huffman encoding function
Node *huffman_encoding(std::vector<char> &C, std::vector<int> &F)
{
    std::vector<Node *> nodes;
    for (size_t i = 0; i < C.size(); ++i)
    {
        nodes.push_back(newNode(F[i], C[i]));
    }

    // Define priority queue with custom comparator
    std::priority_queue<Node *, std::vector<Node *>, Node::Compare> pq;
    for (Node *node : nodes)
    {
        pq.push(node);
    }

    while (pq.size() != 1)
    {
        // Extract two nodes with minimum frequency
        Node *node_x = pq.top();
        pq.pop();
        Node *node_y = pq.top();
        pq.pop();

        // Create a new internal node with these two nodes as children and sum of frequencies
        Node *z = newNode(node_x->freq + node_y->freq, '\0');
        z->left = node_x;
        z->right = node_y;

        // Push this node back into the priority queue
        pq.push(z);
    }

    // Top of the priority queue now contains the root of the Huffman tree
    return pq.top();
}

int main()
{
    std::vector<char> C = {'A', 'B', 'C', 'D', 'E', 'F'};
    std::vector<int> F = {5, 9, 12, 13, 16, 45};

    Node *root = huffman_encoding(C, F);

    std::cout << "Huffman Tree constructed." << std::endl;
    // Note: In C++, we typically don't print a member that doesn't exist for the root node.
    // The root node's character is intentionally set to '\0' (null character).

    delete root; // Don't forget to free memory allocated dynamically
    return 0;
}