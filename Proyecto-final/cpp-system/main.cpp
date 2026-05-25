#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// ==========================
// ESTRUCTURA STUDENT
// ==========================

struct Student {

    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;
};

// ==========================
// NODO HASH
// ==========================

struct Node {

    Student data;
    Node* next;
};

// ==========================
// NODO AVL
// ==========================

struct AVLNode {

    Student data;

    AVLNode* left;
    AVLNode* right;

    int height;
};

// ==========================
// HASH TABLE
// ==========================

class HashTable {

private:

    static const int SIZE = 211;

    Node* table[SIZE];

    int totalStudents;
    int collisions;

public:

    HashTable() {

        totalStudents = 0;
        collisions = 0;

        for(int i = 0; i < SIZE; i++) {

            table[i] = NULL;
        }
    }

    int hashFunction(int id) {

        return id % SIZE;
    }

    void insert(Student student) {

        int index =
        hashFunction(student.student_id);

        Node* temp = table[index];

        while(temp != NULL) {

            if(temp->data.student_id
               == student.student_id) {

                cout << "\nID duplicado\n";
                return;
            }

            temp = temp->next;
        }

        Node* newNode = new Node();

        newNode->data = student;

        newNode->next = NULL;

        if(table[index] != NULL) {

            collisions++;

            newNode->next =
            table[index];
        }

        table[index] = newNode;

        totalStudents++;
    }

    void search(int id) {

        int index =
        hashFunction(id);

        Node* temp = table[index];

        while(temp != NULL) {

            if(temp->data.student_id == id) {

                cout << "\n===== ESTUDIANTE =====\n";

                cout << "ID: "
                     << temp->data.student_id
                     << endl;

                cout << "Nombre: "
                     << temp->data.full_name
                     << endl;

                cout << "Carrera: "
                     << temp->data.career
                     << endl;

                cout << "Semestre: "
                     << temp->data.semester
                     << endl;

                cout << "GPA: "
                     << temp->data.gpa
                     << endl;

                cout << "Skill Score: "
                     << temp->data.skill_score
                     << endl;

                return;
            }

            temp = temp->next;
        }

        cout << "\nEstudiante no encontrado\n";
    }

    void statistics() {

        float loadFactor =
        (float) totalStudents / SIZE;

        cout << "\n===== ESTADISTICAS HASH =====\n";

        cout << "Total estudiantes: "
             << totalStudents
             << endl;

        cout << "Colisiones: "
             << collisions
             << endl;

        cout << "Factor de carga: "
             << loadFactor
             << endl;
    }

    void display() {

        cout << "\n===== TABLA HASH =====\n";

        for(int i = 0; i < SIZE; i++) {

            if(table[i] != NULL) {

                cout << "\nBucket "
                     << i
                     << ": ";

                Node* temp = table[i];

                while(temp != NULL) {

                    cout
                    << "["
                    << temp->data.student_id
                    << " - "
                    << temp->data.full_name
                    << "] -> ";

                    temp = temp->next;
                }

                cout << "NULL";
            }
        }

        cout << endl;
    }
};

// ==========================
// AVL TREE
// ==========================

class AVLTree {

private:

    AVLNode* root;

    int height(AVLNode* node) {

        if(node == NULL)
            return 0;

        return node->height;
    }

    int max(int a, int b) {

        if(a > b)
            return a;

        return b;
    }

    int getBalance(AVLNode* node) {

        if(node == NULL)
            return 0;

        return height(node->left)
             - height(node->right);
    }

    AVLNode* rightRotate(AVLNode* y) {

        AVLNode* x = y->left;

        AVLNode* T2 = x->right;

        x->right = y;

        y->left = T2;

        y->height =
        max(height(y->left),
            height(y->right)) + 1;

        x->height =
        max(height(x->left),
            height(x->right)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {

        AVLNode* y = x->right;

        AVLNode* T2 = y->left;

        y->left = x;

        x->right = T2;

        x->height =
        max(height(x->left),
            height(x->right)) + 1;

        y->height =
        max(height(y->left),
            height(y->right)) + 1;

        return y;
    }

    AVLNode* insertNode(AVLNode* node,
                        Student student) {

        if(node == NULL) {

            AVLNode* newNode =
            new AVLNode();

            newNode->data = student;

            newNode->left = NULL;
            newNode->right = NULL;

            newNode->height = 1;

            return newNode;
        }

        if(student.skill_score
           < node->data.skill_score) {

            node->left =
            insertNode(node->left,
                       student);

        } else {

            node->right =
            insertNode(node->right,
                       student);
        }

        node->height =
        1 + max(height(node->left),
                height(node->right));

        int balance =
        getBalance(node);

        // LEFT LEFT

        if(balance > 1 &&
           student.skill_score <
           node->left->data.skill_score)

            return rightRotate(node);

        // RIGHT RIGHT

        if(balance < -1 &&
           student.skill_score >
           node->right->data.skill_score)

            return leftRotate(node);

        // LEFT RIGHT

        if(balance > 1 &&
           student.skill_score >
           node->left->data.skill_score) {

            node->left =
            leftRotate(node->left);

            return rightRotate(node);
        }

        // RIGHT LEFT

        if(balance < -1 &&
           student.skill_score <
           node->right->data.skill_score) {

            node->right =
            rightRotate(node->right);

            return leftRotate(node);
        }

        return node;
    }

    void inorderTraversal(AVLNode* node) {

        if(node != NULL) {

            inorderTraversal(node->left);

            cout
            << node->data.skill_score
            << " - "
            << node->data.full_name
            << endl;

            inorderTraversal(node->right);
        }
    }

public:

    AVLTree() {

        root = NULL;
    }

    void insert(Student student) {

        root =
        insertNode(root,
                   student);
    }

    void inorder() {

        cout << "\n===== RANKING AVL =====\n";

        inorderTraversal(root);
    }

    void showHeight() {

        cout << "\nAltura AVL: "
             << height(root)
             << endl;
    }
};

// ==========================
// LOAD CSV
// ==========================

void loadCSV(string filename,
             HashTable& hashTable,
             AVLTree& avl) {

    ifstream file(filename);

    if(!file.is_open()) {

        cout << "\nError al abrir CSV\n";
        return;
    }

    string line;

    getline(file, line);
    while(getline(file, line)) {

    if(line.empty()) continue;

    stringstream ss(line);
    Student s;
    string temp;

    if(!getline(ss, temp, ',')) continue;
    s.student_id = stoi(temp);

    if(!getline(ss, s.full_name, ',')) continue;
    if(!getline(ss, s.career, ',')) continue;

    if(!getline(ss, temp, ',')) continue;
    s.semester = stoi(temp);

    if(!getline(ss, temp, ',')) continue;
    s.gpa = stof(temp);

    if(!getline(ss, temp, ',')) continue;
    s.skill_score = stoi(temp);

    hashTable.insert(s);
    avl.insert(s);
}

    

    file.close();

    cout << "\nCSV cargado correctamente\n";
}

// ==========================
// MENU
// ==========================

void menu() {

    cout << "\n===== RED SOCIAL ACADEMICA =====\n";

    cout << "1. Cargar estudiantes CSV\n";
    cout << "2. Mostrar Tabla Hash\n";
    cout << "3. Buscar estudiante\n";
    cout << "4. Mostrar estadisticas Hash\n";
    cout << "5. Mostrar ranking AVL\n";
    cout << "6. Mostrar altura AVL\n";
    cout << "7. Salir\n";

    cout << "Seleccione opcion: ";
}

// ==========================
// MAIN
// ==========================

int main() {

    HashTable hashTable;

    AVLTree avl;

    int option;

    do {

        menu();

        cin >> option;

        switch(option) {

            case 1:

                loadCSV(
                "../dataset/estudiantes.csv",
                hashTable,
                avl);

                break;

            case 2:

                hashTable.display();

                break;

            case 3: {

                int id;

                cout << "\nIngrese ID: ";

                cin >> id;

                hashTable.search(id);

                break;
            }

            case 4:

                hashTable.statistics();

                break;

            case 5:

                avl.inorder();

                break;

            case 6:

                avl.showHeight();

                break;

            case 7:

                cout << "\nSaliendo...\n";

                break;

            default:

                cout << "\nOpcion invalida\n";
        }

    } while(option != 7);

    return 0;
}