#include "Huffman.h"
#include <utility>
#include <iostream>

map<byte, tuple<string, double>> Huffman::symbolsTable;

vector<byte> Huffman::Encode(vector<byte> input)
{
    bytes = std::move(input);

    buildProbabilityTable();

    HuffmanTree* tree = new HuffmanTree();
    tree->buildTree();

    vector<byte> output;

    DoubleLongShortByteUnion doubleLongShortByteUnion;
    doubleLongShortByteUnion.uShort = symbolsTable.size();

    // Size of header; 2 bytes
    output.push_back(doubleLongShortByteUnion.uBytes[1]);
    output.push_back(doubleLongShortByteUnion.uBytes[0]);

    string code = "";

    for (size_t i = 0; i < bytes.size(); i++)
    {
        code += get<0>(symbolsTable.find(bytes[i])->second);
    }

    // Last byte's used bits; 1 byte
    byte lastByteUsedBitsCount = code.length() % 8 == 0 ? 8 : code.length() % 8;
    output.push_back(lastByteUsedBitsCount);

    map<byte, tuple<string, double>>::iterator it;

    // Header; symbol = 1 byte, probability = 8 bytes;
    for (it = symbolsTable.begin(); it != symbolsTable.end(); it++)
    {
        output.push_back(it->first);

        doubleLongShortByteUnion.Double = get<1>(it->second);

        for (int j = 7; j >= 0; j--)
        {
            output.push_back(doubleLongShortByteUnion.uBytes[j]);
        }
    }


    // Code
    for (size_t i = 0; i < code.length() - 8; i += 8)
    {
        string bits8 = code.substr(i, 8);

        std::bitset<8> bitset8(bits8);
        byte byte1 = bitset8.to_ulong();

        output.push_back(byte1);
    }


    string bits8 = code.substr(code.length() - lastByteUsedBitsCount, lastByteUsedBitsCount);
    bits8 += string(8 - lastByteUsedBitsCount, '0');

    std::bitset<8> bitset8(bits8);
    byte byte1 = bitset8.to_ulong();

    output.push_back(byte1);

    return output;
}

void Huffman::buildProbabilityTable()
{
    symbolsTable.clear();

    map<byte, tuple<string, double>>::iterator it;
    size_t size = bytes.size();

    for (size_t i = 0; i < size; i++)
    {
        it = symbolsTable.find(bytes[i]);

        if (it == symbolsTable.end())
        {
            symbolsTable.insert(std::make_pair(
                    bytes[i], std::make_tuple("", 1.0 / size)));
        }

        else
        {
            get<1>(it->second) += 1.0 / size;
        }
    }
}

vector<byte> Huffman::Decode(vector<byte> input)
{
    symbolsTable.clear();

    bytes = std::move(input);

    DoubleLongShortByteUnion doubleLongShortByteUnion;

    doubleLongShortByteUnion.uBytes[1] = bytes[0];
    doubleLongShortByteUnion.uBytes[0] = bytes[1];

    unsigned short symbolTableSize = doubleLongShortByteUnion.uShort;
    bytes.erase(bytes.begin(), bytes.begin() + 2);

    byte lastByteUsedBitsCount = bytes[0];
    bytes.erase(bytes.begin());

    for (size_t i = 0; i < symbolTableSize * SYMBOL_DATA_SIZE; i += SYMBOL_DATA_SIZE)
    {
        byte symbol = bytes[i];

        for (size_t j = i + 1; j < i + 9; j++)
        {
            doubleLongShortByteUnion.uBytes[7 - (j - (i + 1))] = bytes[j];
        }

        double probability = doubleLongShortByteUnion.Double;

        symbolsTable.insert(std::make_pair(
                symbol, std::make_tuple("", probability)));
    }

    HuffmanTree* tree = new HuffmanTree();
    tree->buildTree();

    vector<byte> output;

    string code = "";

    for (size_t i = symbolTableSize * SYMBOL_DATA_SIZE; i < bytes.size(); i++)
    {
        std::bitset<8> bitset8(bytes[i]);

        code += bitset8.to_string();
    }

    output = tree->findSymbols(code, lastByteUsedBitsCount);

    return output;
}

Huffman::HuffmanTree::Node::Node(double probability, byte symbol)
{
    this->probability = probability;
    this->symbol = symbol;
    this->left = nullptr;
    this->right = nullptr;
}

Huffman::HuffmanTree::HuffmanTree()
{
    map<byte, tuple<string, double>>::iterator it;

    for (it = symbolsTable.begin(); it != symbolsTable.end(); it++)
    {
        nodes.push_back(new Node(get<1>(it->second), it->first));
    }

    sort(nodes.begin(), nodes.end(), NodesComparator());
}

void Huffman::HuffmanTree::buildTree()
{
    while (nodes.size() != 1)
    {
        Node* leftNode = nodes.back();
        nodes.pop_back();
        Node* rightNode = nodes.back();
        nodes.pop_back();

        if (isLeaf(leftNode)) leaves.insert(leaves.begin(), leftNode);
        if (isLeaf(rightNode)) leaves.insert(leaves.begin(), rightNode);

        if (leftNode->probability <= rightNode->probability)
        {
            leftNode->code = "0";
            rightNode->code = "1";
        }

        else
        {
            leftNode->code = "1";
            rightNode->code = "0";
        }

        Node* parent = new Node(leftNode->probability + rightNode->probability, ' ');
        parent->left = leftNode;
        parent->right = rightNode;

        int i = 0;
        while (nodes[i]->probability >= parent->probability) i++;
        nodes.insert(nodes.begin() + i, parent);
    }

    createCodes(nodes[0]);

    for (int i = 0; i < leaves.size(); i++)
    {
        get<0>(symbolsTable.find(leaves[i]->symbol)->second) = leaves[i]->code;
    }

    node = nodes[0];

    //deleteTree(nodes[0]);
}

bool Huffman::HuffmanTree::isLeaf(Huffman::HuffmanTree::Node *node)
{
    return (node->left == nullptr && node->right == nullptr);
}

void Huffman::HuffmanTree::deleteTree(Huffman::HuffmanTree::Node *root) {
    if (root == nullptr) return;

    deleteTree(root->left);
    deleteTree(root->right);

    free(root);
}

void Huffman::HuffmanTree::createCodes(Huffman::HuffmanTree::Node *root)
{
    if (root == nullptr) return;

    if (root->right != nullptr) root->right->code = (root->code + root->right->code);
    if (root->left != nullptr) root->left->code = (root->code + root->left->code);

    createCodes(root->right);
    createCodes(root->left);
}

vector<byte> Huffman::HuffmanTree::findSymbols(string code, byte lastByteUsedBitsCount)
{
    vector<byte> output;

    int codePosition = 0;

    for (unsigned long long i = 0; i < code.length() - (8 - lastByteUsedBitsCount); i++)
    {

        if (code[i] == node->left->code[codePosition])
        {
            node = node->left;
        }

        else
        {
            node = node->right;
        }

        codePosition++;

        if (isLeaf(node))
        {
            codePosition = 0;
            output.push_back(node->symbol);
            node = nodes[0];
        }
    }

    return output;
}

Huffman::HuffmanTree::~HuffmanTree()
{
    deleteTree(nodes[0]);
}
