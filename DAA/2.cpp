#include <iostream>
#include <queue>
using namespace std;

struct Node{
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f){
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
};

struct Compare{
    bool operator()(Node *a, Node *b){
        return a->freq > b->freq;
    }
};

void printCodes(Node *root, string code){
    if(!root){
        return;
    }

    if(!root->left && !root->right){
        cout << root->ch << " : " << code << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

void huffman(char chars[], int freqs[], int n){
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for(int i = 0; i < n; i++){
        pq.push(new Node(chars[i], freqs[i]));
    }

    while(pq.size() > 1){
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    cout << "\nHuffman codes: " << endl;
    printCodes(pq.top(), "");
}

int main(){
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    char chars[n];
    int freqs[n];

    cout << "Enter characters: " << endl;
    for(int i = 0; i < n; i++){
        cin >> chars[i];
    }

    cout << "Enter frequencies: " << endl;
    for(int i = 0; i < n; i++){
        cin >> freqs[i];
    }

    huffman(chars, freqs, n);

    return 0;
}

// Time Complexity: O(n log n) => n times pushing in min heap which takes log n
// Space Complexity: O(n) => n nodes + combining n nodes in pairs to form parent