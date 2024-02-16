#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;

// Node structure for the Huffman tree
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// Comparison function for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Function to build the Huffman tree
Node* buildHuffmanTree(const string& S, const int* freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create leaf nodes for each character and push them into the priority queue
    for (int i = 0; i < S.size(); ++i) {
        Node* newNode = new Node(S[i], freq[i]);
        pq.push(newNode);
    }

    // Build the Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        // Create a new internal node with frequency as the sum of frequencies of its children
        Node* newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        // Push the new internal node back into the priority queue
        pq.push(newNode);
    }

    // The top of the priority queue now contains the root of the Huffman tree
    return pq.top();
}

// Function to traverse the Huffman tree in preorder and print Huffman codes
void printHuffmanCodes(Node* root, string code) {
    if (!root) {
        return;
    }

    // If the current node is a leaf node, print its data and code
    if (root->data != '$') {
        cout << "  " << root->data << " : " << code << endl;
    }

    // Traverse left subtree with code appended by '0'
    printHuffmanCodes(root->left, code + '0');

    // Traverse right subtree with code appended by '1'
    printHuffmanCodes(root->right, code + '1');
}

// Main function
int main() {
    string S;
    int n;

    // Input the string length and characters
    cout << "Enter the length of the string: ";
    cin >> n;
    cout << "Enter the characters: ";
    cin >> S;

    // Input the frequencies
    int freq[n];
    cout << "Enter the frequencies: ";
    for (int i = 0; i < n; ++i) {
        cin >> freq[i];
    }

    // Build the Huffman tree
    Node* root = buildHuffmanTree(S, freq);

    // Print Huffman codes in preorder traversal of the tree
    cout << "Huffman codes will be:" << endl;
    printHuffmanCodes(root, "");

    return 0;
}
