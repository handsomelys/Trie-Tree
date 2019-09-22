#include <bits/stdc++.h>
using namespace std;
/*


 /$$$$$$$$                       /$$                       /$$$$$$$$                                                
|__  $$__/                      |__/                      |__  $$__/                                                
   | $$           /$$$$$$        /$$        /$$$$$$          | $$           /$$$$$$         /$$$$$$         /$$$$$$ 
   | $$          /$$__  $$      | $$       /$$__  $$         | $$          /$$__  $$       /$$__  $$       /$$__  $$
   | $$         | $$  \__/      | $$      | $$$$$$$$         | $$         | $$  \__/      | $$$$$$$$      | $$$$$$$$
   | $$         | $$            | $$      | $$_____/         | $$         | $$            | $$_____/      | $$_____/
   | $$         | $$            | $$      |  $$$$$$$         | $$         | $$            |  $$$$$$$      |  $$$$$$$
   |__/         |__/            |__/       \_______/         |__/         |__/             \_______/       \_______/

            
                                                                                                                             
*/    


/*
要求：
1、初始化 在类的内部构建函数中已经实现
2、插入元素 在TrieTree类中的 insert_item方法中已实现
3、删除元素 在del_item方法中已实现
4、查找元素 在search_item 和pri_search_item方法中已实现
5、相关应用 词频统计 已实现
*/
class TrieNode
{
public:
    int count;
    bool isword;
    TrieNode *child[26];

public:
    TrieNode(char word = 0)
    {
        isword = false;
        count = 1;
        memset(child, 0, sizeof(child));
    }
};
class TrieTree
{
private:
    TrieNode *Root;

public:
    TrieTree()
    {
        Root = new TrieNode();
    }
    ~TrieTree()
    {
        destroy_Tree(Root);
    }

    void insert_item(string str)
    {
        if (Root == NULL || str.length() == 0)
        {
            return;
        }
        TrieNode *T = Root;
        string L = str;
        bool isupdate = false;
        for (char c : L)
        {
            if (T->child[c - 'a'] != NULL)
            {
                T = T->child[c - 'a'];
                T->count++;
            }
            else
            {
                TrieNode *temp = new TrieNode();
                T->child[c - 'a'] = temp;
                T = T->child[c - 'a'];
            }
        }
        T->isword = true;
    }

    bool search_item(string str)
    {
        if (Root == NULL || str.length() == 0)
        {
            cout << "NULL" << endl;
            return false;
        }
        TrieNode *T = Root;

        for (char c : str)
        {
            if (T != NULL)
                T = T->child[c - 'a'];
        }
        return (T && T->isword);
    }

    bool pri_search_item(string str)
    {
        if (Root == NULL || str.length() == 0)
        {
            printf("NULL\n");
            return false;
        }
        TrieNode *T = Root;

        for (char c : str)
        {
            if (T != NULL)
            {
                T = T->child[c - 'a'];
            }
        }
        return (T != NULL);
    }
    void destroy_Tree(TrieNode *Root)
    {
        for (int i = 0; i < 26; i++)
        {
            if (Root->child[i] != NULL)
                destroy_Tree(Root->child[i]);
        }
        free(Root);
    }

    int pri_num(string str)
    {
        if (!Root || str.length() == 0)
            return 0;
        if (!pri_search_item(str))
            return 0;
        TrieNode *T = Root;
        for (char c : str)
        {
            if (T)
            {
                T = T->child[c - 'a'];
            }
        }
        if (T)
            return T->count;
        return 0;
    }

    TrieNode *getNode(string str, int k)
    {
        TrieNode *T = Root;
        for (char c : str)
        {
            if (k-- == 0)
                break;
            if (!T)
                T = T->child[c - 'a'];
        }
        return T;
    }

    bool p_isone(TrieNode *child[])
    {
        int numberofpoint = 0;
        for (int i = 0; i < 26; i++)
        {
            if (child[i] != NULL)
            {
                numberofpoint++;
            }
        }
        return numberofpoint == 1 ? true : false;
    }

    bool del_item(string str)
    {
        TrieNode *detach = NULL;
        TrieNode *detachparent = NULL;
        int detachpoint = -1;
        TrieNode *p = Root;
        int index = 0;
        for (int i = 0; i < str.length(); i++)
        {
            index = str.at(i) - 'a';
            if (p->child[index] == NULL)
            {
                return false;
            }
            if (!p_isone(p->child))
            {
                detachparent = p;
                detach = p->child[index];
                detachpoint = i;
            }
            if (detachpoint != -1)
            {
                if (p->count != 0)
                {
                    detachparent = p;
                    detach = p->child[index];
                    detachpoint = i;
                }
            }
            p = p->child[index];
        }
        if (detachpoint == str.length() - 1)
        {
            if (p->count != 0)
            {
                for (int i = 0; i < 26; i++)
                {
                    if (p->child[i] != NULL)
                    {
                        p->count = 0;
                        return true;
                    }
                }
            }
        }
        TrieNode *temp = detach;
        detachparent->child[str.at(detachpoint) - 'a'] = NULL;
        for (int i = detachpoint + 1; i < str.length(); i++)
        {
            index = str.at(i) - 'a';
            temp = detach->child[index];
            delete detach;
            detach = temp;
        }
        delete detach;
        return true;
    }
    int frequency(string str)
    {
        TrieNode *T = Root;
        int id;
        for (char c : str)
        {
            id = c - 'a';
            T = T->child[id];
            if (!T)
                return 0;
        }
        return T->count;
    }
};

main()
{
    TrieTree tree;
    string str;
    cout << "please init a TrieTree" << endl;
    int num;
    cout << "please input the size of this TrieTree" << endl;
    cin >> num;
    cout << "please input the words that you want to save in the tree" << endl;
    for (int i = 0; i < num; i++)
    {

        cin >> str;
        tree.insert_item(str);
    }
    string base = "cao";
    tree.insert_item(base);
    cout << "completed!" << endl;
    cout << "what operation you want to do?" << endl;
    cout << "0、 exit and destroy the whole tree " << endl;
    cout << "1、 search the words" << endl;
    cout << "2、 delete some words" << endl;
    cout << "3、 insert some words into the trie tree" << endl;
    cout << "4、 statistical word frequency " << endl;
    int flag;
    cout << "make your choice" << endl;
    cin >> flag;
    while (1)
    {
        if (flag == 0)
        {
            
            cout << "The tree will be destroyed..." << endl;
            //tree.~TrieTree();
            cout << "Good bye";
            return 0;
        }

        else if (flag == 1)
        {
            cout << "please input the words you want to search" << endl;
            cout << "please input '0' to exit" << endl;
            while (1)
            {
                cin >> str;
                if (!str.compare("0"))
                    break;
                if (tree.search_item(str))
                    cout << "This words are existed" << endl;
                else if (tree.pri_search_item(str))
                    cout << "This words are only other words' pristr" << endl;
                else
                    cout << "This string is not existd" << endl;
            }
        }
        else if (flag == 2)
        {
            cout << "please input the words that you want to del" << endl;
            cin >> str;
            if (tree.del_item(str))
                cout << "These words are del" << endl;
            else
                cout << "These words can not be del, please try again" << endl;
        }
        else if (flag == 3)
        {
            cout << "please input the nums of words that you want to insert" << endl;
            int n;
            cin >> n;
            cout << "please input the words you want to insert" << endl;
            for (int i = 0; i < n; i++)
            {
                cin >> str;
                tree.insert_item(str);
            }
        }
        else if (flag == 4)
        {
            cout << "please input the words that you want to know its frequency" << endl;
            cin >> str;
            cout << tree.frequency(str) << endl;
        }
        cout << "please continue your choice" << endl;
        cin >> flag;
    }
}