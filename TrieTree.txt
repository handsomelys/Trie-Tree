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
class TrieNode
{
public:
    int count;           //统计节点出现次数
    bool isword;         //判断是否构成一个单词
    TrieNode *child[26]; //一个结点延申出最多26个节点（26个字母）

public:
    TrieNode(char word = 0) //构建函数
    {
        isword = false; //初始化
        count = 1;
        memset(child, 0, sizeof(child));
    }
};
class TrieTree
{
private:
    TrieNode *Root; //根节点

public:
    TrieTree() //构建函数
    {
        Root = new TrieNode(); //初始化 分配一个TrieNode空间
    }
    ~TrieTree() //析构函数
    {
        cout << "this tree is destroy" << endl;
        destroy_Tree(Root); //调用摧毁树的那个函数
    }

    void insert_item(string str) //插入函数 将string插入至Trie树里
    {
        //参数为需要存入trie树里的单词（字符串）
        if (Root == NULL || str.length() == 0) //如果节点为空 或传入的字符串为空
        {
            return;
        }
        TrieNode *T = Root;
        string L = str;
        for (char c : L) //将遍历字符串为一个个字符
        {
            if (T->child[c - 'a'] != NULL) //如果该节点存在该字符的子节点存在，则该子节点的count计数+1
            {
                T = T->child[c - 'a'];
                T->count++;
            }
            else
            {
                TrieNode *temp = new TrieNode(); //如果不存在 申请一个新的节点空间
                T->child[c - 'a'] = temp;        //对应索引的节点插入这个新分配空间的节点
                T = T->child[c - 'a'];
            }
        }
        T->isword = true;
    }

    bool search_item(string str) //查找单词是否存在
    {
        //参数为需要存入trie树里的单词（字符串）
        if (Root == NULL || str.length() == 0)
        {
            cout << "NULL" << endl;
            return false;
        }
        TrieNode *T = Root;

        for (char c : str) //通过拆分字符串 分成一个个字符在树的节点查找
        {
            if (T != NULL)
                T = T->child[c - 'a'];
        }
        return (T && T->isword); //如果最后的节点不为空 且遍历的字符可构成单词则返回true
    }

    bool pri_search_item(string str) //查找字符的前缀 原理跟上一个查找单词的函数差不多 只是return的判断条件少了一个判断是否构成单词
    {
        //参数为需要存入trie树里的单词（字符串）
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
    void destroy_Tree(TrieNode *Root) //摧毁整棵树
    {

        for (int i = 0; i < 26; i++)
        {
            if (Root->child[i] != NULL)
                destroy_Tree(Root->child[i]); //递归调用该函数
        }
        free(Root);
    }

    bool p_isone(TrieNode *child[]) //判断该节点是否只有一个子节点
    {
        //参数为需要存入trie树里的单词（字符串）
        int numberofpoint = 0; //统计该节点出现次数
        for (int i = 0; i < 26; i++)
        {
            if (child[i] != NULL)
            {
                numberofpoint++;
            }
        }
        return numberofpoint == 1 ? true : false;
    }

    bool del_item(string str) //删除单词（删除元素）
    {
        //参数为需要存入trie树里的单词（字符串）
        TrieNode *detach = NULL;       //临时存储要删除的节点
        TrieNode *detachparent = NULL; //临时存储要删除节点的子节点
        int detachpoint = -1;
        TrieNode *T = Root;
        int index = 0;
        for (int i = 0; i < str.length(); i++) //挨个遍历 假如发现不存在该单词 直接return false
        {
            index = str.at(i) - 'a';
            if (T->child[index] == NULL)
            {
                return false;
            }
            if (!p_isone(T->child)) //如果该节点不止一个子节点
            {
                detachparent = T; //用临时变量记录一下
                detach = T->child[index];
                detachpoint = i;
            }
            if (detachpoint != -1) //如果记录了要删除的节点
            {
                if (T->count != 0) //如果这个字母出现不止一次
                {
                    detachparent = T; //记录
                    detach = T->child[index];
                    detachpoint = i;
                }
            }
            T = T->child[index];
        }
        if (detachpoint == str.length() - 1) //如果恰是最后一个节点
        {
            if (T->count != 0)
            {
                for (int i = 0; i < 26; i++)
                {
                    if (T->child[i] != NULL)
                    {
                        T->count = 0; //存在的节点的count计数置为0 视为删除
                        return true;
                    }
                }
            }
        }
        TrieNode *temp = detach;                               //临时变量存储要删除的节点
        detachparent->child[str.at(detachpoint) - 'a'] = NULL; //定位到该字母所在位置 指针设为null
        for (int i = detachpoint + 1; i < str.length(); i++)   //定位
        {
            index = str.at(i) - 'a';     //索引
            temp = detach->child[index]; //临时存储 这里的删除操作是数据结构所学的链表的删除
            delete detach;
            detach = temp;
        }
        delete detach;
        return true;
    }
    int frequency(string str) //统计词频
    {
        //参数为需要存入trie树里的单词（字符串）
        TrieNode *T = Root;
        int index;
        for (char c : str)
        {
            index = c - 'a';
            T = T->child[index];
            if (!T)
                return 0;
        }
        return T->count; //返回输入字符串的词频
    }
};

typedef pair<string,int> p;

bool cmpvalue(p& x, p& y)
{
    return x.second>y.second;
}
struct cmpbyvalue
{
    bool operator()(p& x, p& y)
    {
        return x.second>y.second;
    }
};

main() 
{
    TrieTree tree;  //创建TrieTree类实例
    string str; //存放单词的string 类实例
    cout << "please init a TrieTree" << endl;
    int num;    //一开始建立的树的规模
    cout << "please input the size of this TrieTree" << endl;
    cin >> num;
    cout << "please input the words that you want to save in the tree" << endl;
    set<string> words;
    vector<int> fre;
    map<string,int> freq;
    for (int i = 0; i < num; i++)
    {

        cin >> str;
        words.insert(str);
        tree.insert_item(str);  //调用插入单词方法 将字符串插入树中
    }
    string base = "cao";
    tree.insert_item(base);
    cout << "completed!" << endl;
    cout << "what operation you want to do?" << endl;
    cout << "0、 exit and destroy the whole tree " << endl; //开关0 退出程序 摧毁trie树
    cout << "1、 search the words" << endl; //开关1 输入字符串 判断该字符串是否是存在tire树里的单词 或某单词的前缀
    cout << "2、 delete some words" << endl;    // 开关2 删除树中的某单词        
    cout << "3、 insert some words into the trie tree" << endl; //开关3 插入某单词到树中
    cout << "4、 statistical word frequency " << endl;  //开关4  统计字符串在树中的词频
    int flag;   //开关变量 用于选择功能
    cout << "make your choice" << endl;
    cin >> flag;
    while (1)
    {
        if (flag == 0)
        {

            cout << "The tree will be destroyed..." << endl;
            cout << "Good bye"<<endl;
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
            {
                words.erase(str);
                cout << "These words are del" << endl;
            }
                
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
                words.insert(str);
                tree.insert_item(str);
            }
        }
        else if (flag == 4)
        {
            /*
            cout << "please input the words that you want to know its frequency" << endl;
            cin >> str;
            cout << tree.frequency(str) << endl;
            

            for(set<string>::iterator it=words.begin();it!=words.end();it++)
            {
                fre.push_back(tree.frequency(*it));
            }
            sort(fre.begin(),fre.end());
            for(vector<int>::iterator it=fre.begin();it!=fre.end();it++)
            {
                cout<<*it<<endl;
            }
            */
            for(set<string>::iterator it=words.begin();it!=words.end();it++)
            {
                freq.insert(pair<string,int>(*it,tree.frequency(*it)));
            }
            vector<p> Freq(freq.begin(),freq.end());
            sort(Freq.begin(),Freq.end(),cmpbyvalue());
            for(int i=0;i!=Freq.size();i++)
            {
                cout<<Freq[i].first<<":"<<Freq[i].second<<endl;
            }
            
        }
        cout << "please continue your choice" << endl;
        cin >> flag;
    }
}