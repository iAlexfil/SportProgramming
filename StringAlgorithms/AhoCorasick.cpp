#include <bits/stdc++.h>

using namespace std;

struct Aho{
    struct Node{
        int p; // Индекс родителя
        int lastLetter; // Буква по которой пришли
        int suflink = -1;
        int zipSufLink = -1;
        vector<int> ind;
        bool term = false;
        map<int, int> son, go;
        Node() {}
    };

    vector<Node> tree;

    // добавить строку в бор
    void add(string &s){
        int u = 0;
        for(char c: s){
            int cur = c - 'a';
            if(!tree[u].son.count(cur)){
                tree[u].son[cur] = (int)tree.size();
                tree.emplace_back();
                tree.back().lastLetter = cur;
                tree.back().p = u;
            }
            u = tree[u].son[cur];
        }
        tree[u].term = true;
    }
    
    //  вычислить суфф ссылку
    int getSufLink(int u){
        if(tree[u].suflink == -1){
            if(u == 0 or tree[u].p == 0){
                tree[u].suflink = 0;
            }else{
                tree[u].suflink = go(getSufLink(tree[u].p),
                                     tree[u].lastLetter);
            }
        }
        return tree[u].suflink;
    }

    // вычислить сжатую суфф ссылку
    // (в ближайшую терминальную вершину)
    int getZipSufLink(int u){
        if(tree[u].zipSufLink == -1){
            if(u == 0 or tree[u].p == 0)
                tree[u].zipSufLink = 0;
            else{
                int suflink = getSufLink(u);
                if(tree[suflink].term)
                    tree[u].zipSufLink = suflink;
                else
                    tree[u].zipSufLink = getZipSufLink(suflink);
            }
        }
        return tree[u].zipSufLink;
    }

    // переход по состояниям автомата, по символу c
    int go(int u, int c){
        if(!tree[u].go.count(c)){
            if(tree[u].son.count(c))
                tree[u].go[c] = tree[u].son[c];
            else{
                if(u == 0)tree[u].go[c] = 0;
                else tree[u].go[c] = go(getSufLink(u), c);
            }
        }
        return tree[u].go[c];
    }

    Aho(){
        tree.resize(1, Node());
        tree[0].suflink = 0;
        tree[0].zipSufLink = 0;
        tree[0].p = 0;
    }
};

signed main() {
    return 0;
}
