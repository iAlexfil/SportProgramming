#include <bits/stdc++.h>

using namespace std;

using ll = long long;


struct SegmentTreeBeats{
    struct Node{
        int mx, cntMax; // max, count of max
        int secondMax; // second max
        ll sum; // sum
    };

    vector<Node> tree;
    vector<int> a;
    int n;

    // update p from child
    void recalc(int p){
        int lc = p * 2 + 1, rc = p * 2 + 2;
        tree[p].sum = tree[lc].sum + tree[rc].sum;
        tree[p].mx = max(tree[lc].mx, tree[rc].mx);

        tree[p].secondMax = max(tree[lc].secondMax, tree[rc].secondMax);
        if(tree[lc].mx != tree[rc].mx)
            tree[p].secondMax = max(tree[p].secondMax,
                                    min(tree[lc].mx, tree[rc].mx));

        tree[p].cntMax = 0;
        if(tree[p].mx == tree[lc].mx)
            tree[p].cntMax += tree[lc].cntMax;
        if(tree[p].mx == tree[rc].mx)
            tree[p].cntMax += tree[rc].cntMax;
    }

    // update p with min= x
    void updateVal(int p, int x){
        if(x < tree[p].mx){
            tree[p].sum -= (ll)(tree[p].mx - x) * tree[p].cntMax;
            tree[p].mx = x;
        }
    }

    // lazy push to children
    void push(int p){
        int lc = p * 2 + 1, rc = p * 2 + 2;
        int x = tree[p].mx;
        updateVal(lc, x);
        updateVal(rc, x);
    }

    // simple build tree
    void build(int p, int l, int r){
        if(l + 1 == r){
            tree[p].mx = a[l];
            tree[p].secondMax = -1;
            tree[p].cntMax = 1;
            tree[p].sum = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(p * 2 + 1, l, m);
        build(p * 2 + 2, m, r);
        recalc(p);
    }

    // min= x  on [lx...rx)
    void updateMin(int p, int l, int r, int lx, int rx, int x){
        if(rx <= l || lx >= r || tree[p].mx <= x)
            return;
        if(lx <= l && rx >= r && tree[p].secondMax < x){
            updateVal(p, x);
            return;
        }
        push(p);
        int m = (l + r) / 2;
        updateMin(p * 2 + 1, l, m, lx, rx, x);
        updateMin(p * 2 + 2, m, r, lx, rx, x);
        recalc(p);
    }

    void updateMin(int lx, int rx, int x){
        updateMin(0, 0, n, lx, rx, x);
    }

    // sum on [lx...rx)
    ll sumQuery(int p, int l, int r, int lx, int rx){
        if(rx <= l || lx >= r)
            return 0ll;
        if(lx <= l && rx >= r)
            return tree[p].sum;
        push(p);
        int m = (l + r) / 2;
        return sumQuery(p * 2 + 1, l, m, lx, rx) +
                sumQuery(p * 2 + 2, m, r, lx, rx);
    }

    ll sumQuery(int lx, int rx){
        return sumQuery(0, 0, n, lx, rx);
    }

    SegmentTreeBeats(vector<int> &a): a(a){
        n = (int)a.size();
        tree.resize(4 * n);
        build(0, 0, n);
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for(int &i: a){
        cin >> i;
    }
    SegmentTreeBeats segTree(a);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int type, lx, rx;
        cin >> type >> lx >> rx;
        lx--;
        if(type == 1) {
            int val;
            cin >> val;
            segTree.updateMin(lx, rx, val);
        }else{
            cout << segTree.sumQuery(lx, rx) << '\n';
        }
    }

    return 0;
}
