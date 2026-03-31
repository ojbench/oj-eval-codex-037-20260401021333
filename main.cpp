#include <bits/stdc++.h>
#include <iostream>
using namespace std;

namespace DoubleLinkList {

struct NODE {
    int data;
    NODE *next;
    NODE *pre;
    NODE() : data(0), next(nullptr), pre(nullptr) {}
    NODE(int val) : data(val), next(nullptr), pre(nullptr) {}
};

NODE *head = nullptr, *tail = nullptr;
int len = 0;

void Pre() {
    head = new NODE();
    tail = new NODE();
    head->pre = NULL;
    tail->next = NULL;
    head->next = tail;
    tail->pre = head;
}

NODE *move(int i) {
    // Move to the node at position i (0-based) in the list.
    // Since we maintain sentinels, position i corresponds to the i-th data node after head.
    NODE *cur = head;
    for (int j = 0; j <= i; j++) {
        cur = cur->next; // safe by problem guarantee
    }
    return cur;
}

void insert(int i, int x) {
    // Insert value x so that it becomes at position i after insertion.
    // That is, insert before current node at position i.
    // Validity of i is guaranteed by the problem statement.
    NODE *pos = move(i); // node currently at position i (or tail when i==len)
    NODE *node = new NODE(x);
    NODE *prev = pos->pre;
    // link prev <-> node <-> pos
    prev->next = node;
    node->pre = prev;
    node->next = pos;
    pos->pre = node;
    ++len;
}

void remove(int i) {
    // Remove node at position i (0-based). Validity guaranteed.
    NODE *pos = move(i);
    NODE *prev = pos->pre;
    NODE *nxt = pos->next;
    prev->next = nxt;
    nxt->pre = prev;
    delete pos;
    --len;
}

int Get_length() {
    return len;
}

int Query(int i) {
    if (i < 0 || i >= len) return -1;
    NODE *pos = move(i);
    return pos->data;
}

void Print() {
    if (len == 0) {
        cout << -1 << '\n';
        return;
    }
    NODE *cur = head->next;
    bool first = true;
    while (cur != tail) {
        if (!first) cout << ' ';
        cout << cur->data;
        first = false;
        cur = cur->next;
    }
    cout << '\n';
}

void Clear() {
    // delete all nodes including tail sentinel, then delete head
    if (!head) return;
    NODE *cur = head->next;
    while (cur != nullptr) {
        NODE *nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    delete head;
    head = tail = nullptr;
    len = 0;
}

} // namespace DoubleLinkList

int n;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    int op, x, p, ans;
    DoubleLinkList::Pre();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
        case 0:
            ans = DoubleLinkList::Get_length();
            cout << ans << '\n';
            break;
        case 1:
            cin >> p >> x;
            DoubleLinkList::insert(p, x);
            break;
        case 2:
            cin >> p;
            ans = DoubleLinkList::Query(p);
            cout << ans << '\n';
            break;
        case 3:
            cin >> p;
            DoubleLinkList::remove(p);
            break;
        case 4:
            DoubleLinkList::Print();
            break;
        }
    }
    DoubleLinkList::Clear();
    return 0;
}
