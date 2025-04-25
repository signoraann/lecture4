#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

// Структура узла дерева
struct TreeNode {
    int key;          
    string data;     
    TreeNode* left;  
    TreeNode* right;  
    int height;
}*root;

int getHeight(TreeNode* node) {
    if (node != nullptr) {
        return node->height;
    }
    else {
        return 0;
    }
}

// Обновление высоты узла
void updateHeight(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    int leftHeight = 0;
    if (node->left != nullptr) {
        leftHeight = node->left->height;
    }

    int rightHeight = 0;
    if (node->right != nullptr) {
        rightHeight = node->right->height;
    }

    node->height = max(leftHeight, rightHeight) + 1;
}

int getBalance(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }

    int leftHeight = 0;
    if (node->left != nullptr) {
        leftHeight = node->left->height;
    }

    int rightHeight = 0;
    if (node->right != nullptr) {
        rightHeight = node->right->height;
    }

    return leftHeight - rightHeight;
}


TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    y->left = x->right;
    x->right = y;
    updateHeight(y);
    updateHeight(x);
    return x;
}

TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    x->right = y->left;
    y->left = x;
    updateHeight(x);
    updateHeight(y);
    return y;
}



TreeNode* balanceNode(TreeNode* node) {
    if (!node) return nullptr;

    // Обновляем высоту текущего узла
    updateHeight(node);

    int balance = getBalance(node);

  
    if (balance > 1) {  // Левое поддерево слишком высокое
        if (getBalance(node->left) < 0) {  
            node->left = leftRotate(node->left);
        }
        return rightRotate(node);  
    }

    if (balance < -1) {  //правое слишком высокое
        if (getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
        }
        return leftRotate(node);  
    }

    return node;  
}

// Создание нового узла
TreeNode* createNode(int key, const string& data){
    TreeNode* newNode = new TreeNode;
    newNode->key = key;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}


// Добавление узла в дерево
TreeNode* insertNode(TreeNode* node, int key, const string& data) {
    if (node == nullptr) {
        return createNode(key, data);
    }

    if (key < node->key) {
        node->left = insertNode(node->left, key, data);
    }
    else if (key > node->key) {
        node->right = insertNode(node->right, key, data);
    }
    else {
        return node; 
    }

    return balanceNode(node);
}

// Поиск узла по ключу
TreeNode* findNode(TreeNode* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return findNode(root->left, key);
    }
    else {
        return findNode(root->right, key);
    }
}

// Поиск минимального узла в поддереве
TreeNode* findMinNode(TreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Удаление узла по ключу
TreeNode* deleteNode(TreeNode* node, int key) {
    if (root == nullptr) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        // Узел с одним или без 
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Узел с двумя
        TreeNode* temp = findMinNode(root->right);
        root->key = temp->key;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
    if (node == nullptr) return nullptr;

    return balanceNode(node);
}

// Вывод дерева с отступами
void printTree(TreeNode* root, int level = 0) {
    if (root != nullptr) {
        printTree(root->right, level + 1);
        for (int i = 0; i < level; i++) cout << "    ";
        cout << root->key << " (" << root->data << ")" << endl;
        printTree(root->left, level + 1);
    }
}

// Обходы дерева
void preOrderTraversal(TreeNode* root) {//прямой(клп))
    if (root != nullptr) {
        cout << root->key << ": " << root->data << endl;
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void postOrderTraversal(TreeNode* root) {//обратный(лпк)
    if (root != nullptr) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        cout << root->key << ": " << root->data << endl;
    }
}

void inOrderTraversal(TreeNode* root) {//по возрастанию(лкп)
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << root->key << ": " << root->data << endl;
        inOrderTraversal(root->right);
    }
}

// Количество узлов в левом поддереве (индивидуальное задание)
int countLeftNodes(TreeNode* root) {
    if (root == nullptr || root->left == nullptr) return 0;
    int count = 1;
    count += countLeftNodes(root->left->left);
    count += countLeftNodes(root->left->right);
    return count;
}

// Освобождение памяти
void clearTree(TreeNode*& root) {
    if (root != nullptr) {
        clearTree(root->left);
        clearTree(root->right);
        delete root;
        root = nullptr;
    }
}

// Функция для добавления данных из массива
void insertFromArray(TreeNode*& root) {
    int count;
    cout << "Сколько записей добавить? ";
    cin >> count;


    for (int i = 0; i < count; i++) {
        int key;
        string data;
        
        cout << "Запись " << i + 1 << ":" << endl;
        cout << "Введите ключ: ";
        cin >> key;
        cout << "Введите данные: ";
        cin.ignore();
        getline(cin, data);
        
        root = insertNode(root, key, data);
    }
   
}
//Удаление дерева полностью 
void clearTreeIterative(TreeNode*& root) {
    while (root != nullptr) {
        if (root->left != nullptr) {
            TreeNode* left = root->left;
            root->left = left->right;
            left->right = root;
            root = left;
        }
        else {
            TreeNode* toDelete = root;
            root = root->right;
            delete toDelete;
        }
    }
}

bool isTreeBalanced(TreeNode* root) {
    if (root == nullptr) return true;

    int balance = getBalance(root);
    if (balance < -1 || balance > 1) return false;

    return isTreeBalanced(root->left) && isTreeBalanced(root->right);
}


int main() {
    TreeNode* root = nullptr;
    int choice;

    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    do {
        cout << "\nВыберите действие:" << endl;
        cout << "1. Добавить запись" << endl;
        cout << "2. Внести информацию из массива" << endl;
        cout << "3. Сбалансировать дерево" << endl;
        cout << "4. Индивидуальное задание" << endl;
        cout << "5. Найти информацию по заданному ключу" << endl;
        cout << "6. Распечатать информацию прямым обходом" << endl;
        cout << "7. Распечатать информацию обратным обходом" << endl;
        cout << "8. Распечатать информацию в порядке возрастания" << endl;
        cout << "9. Удалить информацию по заданному ключу" << endl;
        cout << "10. Просмотр дерева" << endl;
        cout << "11. Удаление всего дерева" << endl;
        cout << "0. Выход" << endl;
        cout << "> ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int key;
            string data;
            cout << "Введите ключ: ";
            cin >> key;
            cout << "Введите данные: ";
            cin.ignore();
            getline(cin, data);
            root = insertNode(root, key, data);
            break;
        }
        case 2: {
            insertFromArray(root);
            break;
        }
        case 3: {
            if (isTreeBalanced(root)) {
                cout << "Дерево сбалансировано." << endl;
            }
            else {
                cout << "Дерево не сбалансировано!" << endl;
                cout << "Выполняется балансировка..." << endl;
                cout << "Дерево сбалансировано." << endl;
            }
            break;
        }
        case 4: {
            cout << "Количество узлов в левом поддереве: "
                << countLeftNodes(root) << endl;
            break;
        }
        case 5: {
            int key;
            cout << "Введите ключ для поиска: ";
            cin >> key;
            TreeNode* found = findNode(root, key);
            if (found != nullptr) {
                cout << "Найдено: " << found->key << ": "
                    << found->data << endl;
            }
            else {
                cout << "Запись не найдена!" << endl;
            }
            break;
        }
        case 6: {
            cout << "Прямой обход:" << endl;
            preOrderTraversal(root);
            break;
        }
        case 7: {
            cout << "Обратный обход:" << endl;
            postOrderTraversal(root);
            break;
        }
        case 8: {
            cout << "В порядке возрастания:" << endl;
            inOrderTraversal(root);
            break;
        }
        case 9: {
            int key;
            cout << "Введите ключ для удаления: ";
            cin >> key;
            root = deleteNode(root, key);
            break;
        }
        case 10: {
            cout << "Структура дерева:" << endl;
            printTree(root);
            break;
        }
        case 11:
            cout << "Дерево удалено" << endl;
            clearTreeIterative(root);
            break;
        case 0: {
            clearTree(root);
            cout << "Выход..." << endl;
            break;
        }
        default: {
            cout << "Неверный выбор!" << endl;
        }
        }
    } while (choice != 0);

    return 0;
}