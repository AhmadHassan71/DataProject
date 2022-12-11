#pragma once
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;



template <typename T>
struct node
{
    T data;
    string cause113, cause, state;
    double deathrate;
    int death, year, color;
    int height;
    node <T>* left;
    node <T>* right;
    node <T>* parent;

    friend void AVLwrite(const node<T>* object)
    {
        ofstream myFile("AVLfiles/AVL.dat", ios::binary | ios::app);
        myFile.write((char*)&object, sizeof(object));
        myFile.close();
    }

    friend void writeRB(const node<T>* object)
    {
        ofstream myFile("RedBlackfiles/RB.dat", ios::binary | ios::app);
        myFile.write((char*)&object, sizeof(object));
        myFile.close();
    }
    
};

template <typename T>
class AVL
{
public:
    node<T>* root;


    AVL()
    {
        cout << "\n created \n";
        root = NULL;

    }

    AVL(T val)
    {
        root = new node<T>;
        root->data = val;
    }

    T max(T num1, T num2)
    {
        if (num1 > num2)
            return num1;
        return num2;
    }

    int getHeight()
    {
        if (!root)
            return 0;

        int var1 = getHeight(root->left);
        int var2 = getHeight(root->right);

        return (1 + max(var1, var2));
    }
    int getHeight(node<T>* root)
    {
        if (!root)
            return 0;

        int var1 = getHeight(root->left);
        int var2 = getHeight(root->right);

        return (1 + max(var1, var2));
    }

    T getMin()
    {
        node<T>* curr = root;
        while (!curr->left)
        {
            curr = curr->left;
        }
        return curr->data;
    }

    node<T>* getMin(node<T>* root)
    {

        if (!root)
            return 0;

        if (!root->left)
            return root;

        node<T>* temp = root->left;

        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }

    node<T>* rotateRight(node<T>* root)
    {
        node<T>* temp = root->left;
        node<T>* temp2 = temp->right;
        temp->right = root;
        root->left = temp2;
        root->height = getHeight(root);
        temp->height = getHeight(temp);

        return temp;
    }

    node<T>* rotateLeft(node<T>* root)
    {
        node<T>* temp = root->right;
        node<T>* temp2 = temp->left;
        temp->left = root;
        root->right = temp2;
        root->height = getHeight(root);
        temp->height = getHeight(temp);

        return temp;
    }

    node<T>* retrieve(T id)      //use in Range function
    {
        node<T>* nodeptr = root;

        while (nodeptr)
        {
            if (nodeptr->data == id)
                return nodeptr;
            else if (nodeptr->data > id)
            {
                nodeptr = nodeptr->left;
            }
            else if (nodeptr->data < id)
            {
                nodeptr = nodeptr->right;
            }
        }
        return NULL;
    }

    void levelOrder(node<T>* Node)
    {
        if (Node == NULL)
            return;

        queue<node<T>*> q;
        q.push(Node);

        while (q.empty() == false)
        {
            node<T>* temp = q.front();
            cout << temp->data << "->";
            q.pop();
            if (temp->left)
            {
                q.push(temp->left);
            }
            if (temp->right)
            {
                q.push(temp->right);
            }

        }
    }
    // Inorder traversal
    void inorderTraversal(node<T>* Node)
    {
        if (Node == NULL)
            return;

        inorderTraversal(Node->left);
        cout << Node->data << "->";
        inorderTraversal(Node->right);
    }
    void inorderTraversal()
    {
        inorderTraversal(root);
    }
    void levelOrder()
    {
        levelOrder(root);
    }


    int getBalanceFactor(node<T>* Node)
    {
        if (!Node)
            return 0;
        else
        {
            return getHeight(Node->left) - getHeight(Node->right);
        }
    }

    node<T>* insertNode(T val,int year,string cause113,string cause,string state,int death,  double deathrate)
    {
        root= insertNode(root, val,year,cause113,cause,state,death,deathrate);
        return root;
    }

    node<T>* insertNode(node<T>* root, T val, int year, string cause113, string cause, string state, int death, double deathrate)
    {
        node<T>* temp = new node<T>;
        temp->data = val;
        temp->year = year;
        temp->cause113 = cause113;
        temp->cause = cause;     
        temp->state = state;
        temp->death = death;
        temp->deathrate = deathrate;
        temp->right = temp->left = NULL;
        if (!root)
        {
            root = temp;
            return root;
        }


        if (val < root->data)
        {
            root->left = insertNode(root->left, val, year, cause113, cause, state, death, deathrate);
        }
        else if (val > root->data)
        {
            root->right = insertNode(root->right, val, year, cause113, cause, state, death, deathrate);
        }
        else
            return root;
        
            root->height = getHeight(root);
            int bf = getBalanceFactor(root);
            if (bf > 1)
            {
                if (val < root->left->data)
                {
                    return rotateRight(root);
                }
                else if (val > root->left->data)
                {
                    root->left = rotateLeft(root->left);
                    return rotateRight(root);
                }
            }
            if (bf < -1)
            {
                if (val > root->right->data)
                {
                    return rotateLeft(root);
                }
                else if (val < root->left->data)
                {
                    root->right = rotateRight(root->right);
                    return rotateLeft(root);
                }
            }
        
        return root;
    }


    void delNode(T val)
    {
        root = delNode(root, val);
        cout << "Deleted node with : " << val << endl;

    }
    node<T>* delNode(node<T>* Node, T val)
    {
        if (val < Node->data)
        {
            Node->left = delNode(Node->left, val);
        }
        else if (val > Node->data)
        {
            Node->right = delNode(Node->right, val);
        }
        else
        {
            if (!Node->left && !Node->right)
            {
                return NULL;
            }
            else if (!Node->left)
            {
                node<T>* temp = Node->right;
                free(Node);
                return temp;
            }
            else if (!Node->right)
            {
                node<T>* temp = Node->left;
                free(Node);
                return temp;
            }
            node<T>* temp = getMin(Node->right);

            Node->data = temp->data;
            Node->right = delNode(Node->right, temp->data);
        }


        if (!Node)
            return Node;

        Node->height = getHeight(Node);
        int bf = getBalanceFactor(Node);
        if (bf > 1)
        {
            if (getBalanceFactor(Node->left) >= 0)
                return rotateRight(Node);
            else
            {
                Node->left = rotateLeft(root->left);
                return rotateRight(Node);
            }

        }
        if (bf < -1)
        {
            if (getBalanceFactor(Node->right) >= 0)
            {
                return rotateLeft(Node);
            }
            else
            {
                Node->right = rotateRight(root->right);
                return rotateLeft(Node);
            }
        }
        return Node;
    }

    void AVLprint(node<T>* Node)
    {
       
        if (Node == NULL)
            return;
        AVLprint(Node->left);
        AVLwrite(Node);
        AVLprint(Node->right);
    }
    
};

ostream& operator<<(ostream& output, const node<int>* R)
{
    output << R->data << "," << R->year << ",\"" << R->cause113 << "\"," << R->cause << "," << R->state << "," << R->death << "," << R->deathrate << endl;
    return output;

}

void readAVL(int num)
{
    /*node<int>* temp;
    ifstream myFile("AVLfiles/AVL.dat", ios::binary | ios::app);
    while (myFile.read((char*)&temp, sizeof(temp))) {
        cout << temp;
    }
    myFile.close();*/

    string path = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv";
    string path2 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_2.csv";
    string path3 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_3.csv";
    string path4 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_4.csv";
    string path5 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_5.csv";
    string path6 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_6.csv";
    string path7 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_7.csv";
    string path8 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_8.csv";
    string path9 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_9.csv";
    string path10 = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_10.csv";

    switch (num)
    {
    case 1:
        break;
    case 2:
        path = path2;
        break;
    case 3:
        path = path3; break;
    case 4:
        path = path4; break;
    case 5:
        path = path5; break;
    case 6:
        path = path6; break;
    case 7:
        path = path7; break;
    case 8:
        path = path8; break;
    case 9:
        path = path9; break;
    case 10:
        path = path10; break;
    }
    //string path = "datafiles/NCHS_-_Leading_Causes_of_Death__United_States_1.csv";

    fstream f;
    f.open(path, ios::in);
    int i = 1;
    string line, strobj, cause113, cause, state;
    double deathrate = 0;
    int death = 0, id = 0, year = 0;

    getline(f, line);
    //getline(f, strobj);
    int con = 0;
    while (f.peek() != EOF)
    {
        //getline(f, strobj, ',');
        //getline(f, strobj, ',');

        getline(f, line, ',');
        //cout<<line;
        id = stoi(line);
        getline(f, line, ',');
        //cout<<line;
        year = stoi(line);
        getline(f, line, ',');
        strobj = line;
        if (line[0] == '\"')
        {
            getline(f, line, ',');
            strobj += line;
        }
        //cout<<" "<<strobj<<" ";
        cause113 = strobj;
        //getline(f, strobj, '\"');


        getline(f, line, ',');
        //getline(f, strobj, ',');
        cause = line;
        getline(f, line, ',');
        //getline(f, strobj, ',');

        state = line;
        getline(f, line, ',');
        //getline(f, strobj, ',');
        //cout<<" "<<line;
        death = stoi(line);
        getline(f, line, '\n');
        //getline(f, strobj, '\n');

        deathrate = stod(line);
        std::cout << "\n" << id;
        std::cout << " " << year;
        std::cout << " " << cause113;
        std::cout << " " << cause;
        std::cout << " " << state;
        std::cout << " " << death;
        std::cout << " " << deathrate<<endl;

        //obj.insertNode(id,year,cause113,cause,state,death,deathrate,1);

    }
}



void updateAVL(int id, string updated_state)
{
    node<int>* temp;
    fstream myFile("AVLfiles/AVL.dat", ios::in | ios::out | ios::binary);
    while (myFile.read((char*)&temp, sizeof(temp)))
    {
        if (temp->data == id)
        {
            temp->state=(updated_state);
            

            int current = myFile.tellg();
            int oneblock = sizeof(temp);
            myFile.seekg(current - oneblock);
            myFile.write((char*)&temp, sizeof(temp));
            //temp.display();
            myFile.close();
        }
    }
}
void DeleteAVL(int id)
{
    node<int>* temp;
    fstream myFile("AVLfiles/AVL.dat", ios::in | ios::out | ios::binary);
    while (myFile.read((char*)&temp, sizeof(temp)))
    {
        if (temp->data== id) {
            delete temp;
            temp = NULL;
            int current = myFile.tellg();
            int oneblock = sizeof(temp);
            myFile.seekg(current - oneblock);
            myFile.write((char*)&temp, sizeof(temp));
            myFile.close();
        }
    }
}
