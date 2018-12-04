#include <bits/stdc++.h>
using namespace std;

void build(int node, int start, int end, int *tree, int *a) {
    if(start == end) tree[node] = a[start]; //single element present
    else {
        int mid = (start+end)/2;
        
        build(2*node, start, mid, tree, a); // left child
        build(2*node+1, mid+1, end, tree, a); // right child
    
        if(tree[2*node] < tree[2*node+1]) tree[node] = tree[2*node];
        else tree[node] = tree[2*node+1];
    }
}

void update(int node, int start, int end, int index, int value, int *tree, int *a) {
    if(start == end) {
        a[index] = value;
        tree[node] = value;
    } 
    else {
        int mid = (start+end)/2;
        
        if(index >= start && index <= mid) update(2*node,start,mid,index,value, tree, a);
        else update(2*node+1,mid+1,end,index,value, tree, a);
        
        if(tree[2*node] < tree[2*node+1]) tree[node] = tree[2*node];
        else tree[node] = tree[2*node+1];
    }
}

int query(int node, int start, int end, int l, int r, int *tree) {
    if(l > end || start > r) return 100005;
    if(l<=start && r>=end) return tree[node];
    
    int ans1, ans2;
    int mid = (start+end)/2;
    
    ans1 = query(2*node,start,mid,l,r, tree);
    ans2 = query(2*node+1,mid+1,end,l,r, tree);
    
    if(ans1 < ans2) return ans1;
    else return ans2;
}

int main() {
    
    int tree[2000005] = {};
    int a[100005] = {};
    
    int n, q, i;
    cin >> n >> q;
    
    for(i = 1; i<=n; i++) cin >> a[i];
    
    build(1, 1, n, tree, a); 
    
    while(q--) {
        char b;
        int x, y;
        cin >> b >> x >> y;
        
        if(b == 'q') cout<<query(1, 1, n, x, y, tree)<<'\n';
        else update(1, 1, n, x, y, tree, a);
    }
}
