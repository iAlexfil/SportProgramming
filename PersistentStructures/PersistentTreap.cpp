// return true with chance a / (a + b)
bool rbst(int a, int b){
    return rnd() % (a + b) < a;
}
 
struct PersistentTreap{
    struct Node{
        int sz, sm;
        int x;
        int lc, rc;
        Node(){
            sz = sm = x = 0;
            lc = -1, rc = -1;
        }
    };
 
    vector<Node> tree;
 
    int size(int v){
        if(v == -1)return 0;
        return tree[v].sz;
    }
 
    int sum(int v){
        if(v == -1)return 0;
        return tree[v].sm;
    }
 
    int create_node(int v, int lc, int rc){
        int ind = tree.size();
        tree.emplace_back();
        tree[ind].lc = lc;
        tree[ind].rc = rc;
        tree[ind].sm = sum(lc) + sum(rc) + tree[v].x;
        tree[ind].sz = size(lc) + 1 + size(rc);
        tree[ind].x = tree[v].x;
        return ind;
    }
    int create_node(int x){
        int ind = tree.size();
        tree.emplace_back();
        tree[ind].x = x;
        tree[ind].sz = 1;
        tree[ind].sm = x;
        return ind;
    }
 
    pii split(int v, int k){
        if(k == 0)return {-1, v};
        if(k >= tree[v].sz)return {v, -1};
        if(k <= size(tree[v].lc)){
            auto [l, r] = split(tree[v].lc, k);
            int u = create_node(v, r, tree[v].rc);
            return {l, u};
        }else{
            auto [l, r] =
                    split(tree[v].rc, k - 1 - size(tree[v].lc));
            int u = create_node(v, tree[v].lc, l);
            return {u, r};
        }
    }
 
    int merge(int l, int r){
        if(l == -1)return r;
        if(r == -1)return l;
        if(rbst(size(l), size(r))){
            int v = merge(tree[l].rc, r);
            int u = create_node(l, tree[l].lc, v);
            return u;
        }else{
            int v = merge(l, tree[r].lc);
            int u = create_node(r, v, tree[r].rc);
            return u;
        }
    }
};
