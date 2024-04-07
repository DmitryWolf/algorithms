#include <bits/stdc++.h>
using namespace std;

enum Color {RED, BLACK};

template<class T>
class RBTree{
private:
    struct Node{
        T data_;
        Color color_;
        Node* left_;
        Node* right_;
        Node* parent_;
        Node() = default;
        Node(T value, Color c = RED, Node* l = NULL, Node* r = NULL, Node* p = NULL) :
        data_(value), color_(c), left_(l), right_(r), parent_(p) {}
        Node(Node* p = NULL, Color c = RED, Node* l = NULL, Node* r = NULL) : parent_(p){}
        ~Node() = default;
    };
    Node* root_;
    size_t Size_;
    size_t Height_;

    void LeftRotate(Node* x) { // левая рука
        if (x->right_ != NULL) {
            Node *y = x->right_;
            x->right_ = y->left_;
            if (y->left_ != NULL)
                y->left_->parent_ = x;

            y->parent_ = x->parent_;
            if (x->parent_ == NULL)
                root_ = y;
            else {
                if (x == x->parent_->left_)
                    x->parent_->left_ = y;
                else
                    x->parent_->right_ = y;
            }
            y->left_ = x;
            x->parent_ = y;
        }
    }
    void RightRotate(Node* y) {// правая рука
        if (y->left_ != NULL) {
            Node *x = y->left_;
            y->left_ = x->right_;
            if (x->right_ != NULL)
                x->right_->parent_ = y;

            x->parent_ = y->parent_;
            if (y->parent_ == NULL)
                root_ = x;
            else {
                if (y == y->parent_->right_)
                    y->parent_->right_ = x;
                else
                    y->parent_->left_ = x;
            }
            x->right_ = y;
            y->parent_ = x;
        }
    }
    void fixInsertion(Node* t){
        if (t == root_){
            t->color_ = BLACK;
            return;
        }
        while (t->parent_ != NULL && t->parent_->parent_ != NULL && t->parent_->color_ == RED) { // нарушается 3 свойство
            if (t->parent_->parent_->left_ == t->parent_){ // если отец - левый ребенок
                if (t->parent_->parent_->right_ != NULL && t->parent_->parent_->right_->color_ == RED){ // если есть красный дядя
                    t->parent_->color_ = BLACK;
                    t->parent_->parent_->right_->color_ = BLACK;
                    t->parent_->parent_->color_ = RED;
                    t = t->parent_->parent_;
                }
                else {
                    if (t->parent_->right_ == t){
                        t = t->parent_;
                        LeftRotate(t);
                    }
                    t->parent_->color_ = BLACK;
                    t->parent_->parent_->color_ = RED;
                    RightRotate(t->parent_->parent_);
                }
            }
            else if (t->parent_->parent_->right_ == t->parent_) { // если отец - правый ребенок
                if (t->parent_->parent_->left_ != NULL && t->parent_->parent_->left_->color_ == RED){ // если есть красный дядя
                    t->parent_->color_ = BLACK;
                    t->parent_->parent_->left_->color_ = BLACK;
                    t->parent_->parent_->color_ = RED;
                    t = t->parent_->parent_;
                }
                else{
                    if (t->parent_->left_ == t){
                        t = t->parent_;
                        RightRotate(t);
                    }
                    t->parent_->color_ = BLACK;
                    t->parent_->parent_->color_ = RED;
                    LeftRotate(t->parent_->parent_);
                }
            }
        }
        root_->color_ = BLACK;
    }


    void removeFix(Node* node, Node* parent) {
        Node* othernode;
        size_t cnt = 0;
        while (cnt < Size_ + 10 && ((!node) || (node->color_ == BLACK && node != root_))) {
            cnt++; //---------------
            if (parent != NULL && parent->left_ == node) {
                if (parent->right_ != NULL) {
                    othernode = parent->right_;
                    if (othernode->color_ == RED) {
                        othernode->color_ = BLACK;
                        parent->color_ = RED;
                        LeftRotate(parent);
                        othernode = parent->right_;
                    } else {
                        if (!(othernode->right_) || othernode->right_->color_ == BLACK) {
                            if (othernode->left_ != NULL) {
                                othernode->left_->color_ = BLACK; //-------
                            }
                            othernode->color_ = RED;
                            RightRotate(othernode);
                            othernode = parent->right_;
                        }
                        othernode->color_ = parent->color_;
                        parent->color_ = BLACK;
                        if (othernode->right_ != NULL) {
                            othernode->right_->color_ = BLACK;
                        }
                        LeftRotate(parent);
                        node = root_;
                        break;
                    }
                }
            }
            else
            {
                if (parent->left_ != NULL) {
                    othernode = parent->left_;
                    if (othernode->color_ == RED) {
                        othernode->color_ = BLACK;
                        parent->color_ = RED;
                        RightRotate(parent);
                        othernode = parent->left_;
                    }
                    if (othernode != NULL) {
                        if ((!othernode->left_ || othernode->left_->color_ == BLACK) &&
                            (!othernode->right_ || othernode->right_->color_ == BLACK)) {
                            othernode->color_ = RED;
                            node = parent;
                            parent = node->parent_;
                        } else {
                            if (!(othernode->left_) || othernode->left_->color_ == BLACK) {
                                if (othernode->right_ != NULL) {
                                    othernode->right_->color_ = BLACK;
                                }
                                othernode->color_ = RED;
                                LeftRotate(othernode);
                                othernode = parent->left_;
                            }
                            othernode->color_ = parent->color_;
                            parent->color_ = BLACK;
                            if (othernode->left_ != NULL) {
                                othernode->left_->color_ = BLACK;
                            }
                            RightRotate(parent);
                            node = root_;
                            break;
                        }
                    }
                    else{
                        break;
                    }
                }
            }
        }
        if (node) {
            node->color_ = BLACK;
        }
    }

    void destroy(Node*& node){
        if (node == NULL){
            return;
        }
        destroy(node->left_);
        destroy(node->right_);
        delete node;
        node = nullptr;
    }
    Node* find(Node* &node, const T& key){
        if (node == NULL || node->data_ == key){
            return node;
        }
        else{
            if (key < node->data_){
                return find(node->left_, key);
            }
            else{
                return find(node->right_, key);
            }
        }
    }

    void subHeight(size_t& maxH, size_t& tempH, Node* &node, size_t& is){
        if (node->left_ != NULL){
            if (is == 0){
                tempH++;
            }
            else{
                if (node->color_ == BLACK){
                    tempH++;
                }
            }
            subHeight(maxH, tempH, node->left_, is);
            maxH = max(maxH, tempH);
            if (is == 0) {
                tempH--;
            }
            else{
                if (node->color_ == BLACK){
                    tempH--;
                }
            }
        }
        if (node->right_ != NULL){
            if (!is){
                tempH++;
            }
            else{
                if (node->color_ == BLACK){
                    tempH++;
                }
            }
            subHeight(maxH, tempH, node->right_, is);
            maxH = max(maxH, tempH);
            if (!is) {
                tempH--;
            }
            else{
                if (node->color_ == BLACK){
                    tempH--;
                }
            }
        }
    }
public:
    RBTree() : Size_(0), Height_(0){}
    ~RBTree(){
        destroy(root_);
    }
    void insert(T key){
        if (Size_ == 0){
            root_ = new Node(key, BLACK);
            Size_++;
            return;
        }
        Node* t = new Node(key);
        Node* x = root_;
        Node* y = NULL;
        while (x != NULL){
            y = x;
            if (t->data_ > x->data_){
                x = x->right_;
            }
            else{
                x = x->left_;
            }
        }
        t->parent_ = y;
        if (y != NULL){
            if (t->data_ > y->data_){
                y->right_ = t;
            }
            else{
                y->left_ = t;
            }
        }
        else{
            root_ = t;
        }
        t->color_ = RED;
        Size_++;
        fixInsertion(t);
    }

    void erase(T key) {
        Node* t = find(key);
        Node* child;
        Node* parent;
        Color color;
        // Левый и правый узлы удаленного узла не пусты (не конечные узлы)
        if (t->left_ != NULL && t->right_ != NULL){ //два сына
            Node* temp = t->right_;
            // Найти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
            while(temp->left_ != NULL){
                temp = temp->left_;
            }
            // Случай, когда удаленный узел не является корневым узлом
            if (t->parent_ != NULL){
                if (t->parent_->left_ == t){
                    t->parent_->left_ = temp;
                }
                else{
                    t->parent_->right_ = temp;
                }
            }
            else{ // Ситуация с корневым узлом
                root_ = temp;
            }
            // child - это правильный узел, который заменяет узел и является узлом, который требует последующей корректировки
            // Поскольку замена является преемником, он не может иметь левого дочернего узла
            // Аналогично, у узла-предшественника не может быть правого дочернего узла
            color = temp->color_;
            child = temp->right_;
            parent = temp->parent_;

            // Удаленный узел является родительским узлом замещающего узла (repalce)
            if (parent == t){
                parent = temp;
            }
            else{
                // Существование дочернего узла
                if (child != NULL){
                    child->parent_ = parent;
                }
                parent->left_ = child;
                temp->right_ = t->right_;
                t->right_->parent_ = temp; //---
            }
            temp->parent_ = t->parent_;
            temp->color_ = t->color_;
            temp->left_ = t->left_;
            t->left_->parent_ = temp;
            Size_--;
            if (color == BLACK){
                if (Size_ >= 2) {
                    removeFix(child, parent);
                }
            }
            delete t;
            return;
        }
        // Когда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
        if (t->left_ != NULL){
            child = t->left_;
        }
        else{
            child = t->right_;
        }
        parent = t->parent_;
        color = t->color_;
        if (child){
            child->parent_ = parent;
        }
        // Удаленный узел не является корневым узлом
        if (parent){
            if (t == parent->left_){
                parent->left_ = child;
            }
            else{
                parent->right_ = child;
            }
        }
            // Удаленный узел является корневым узлом
        else{
            root_ = child;
        }
        Size_--;
        if (color == BLACK){
            if (Size_ >= 2) {
                removeFix(child, parent);
            }
        }
        delete t;
        if (Size_ > 0){
            root_->color_ = BLACK;
        }
    }
    Node* find(T key){
        return find(root_, key);
    }

    size_t size(){
        return Size_;
    }
    size_t height(){
        size_t MaxH = 0, tempH = 0, is = 0;
        subHeight(MaxH, tempH, root_, is);
        return MaxH + 1;
    }
    size_t black_height(){
        if (Size_ == 1){
            return (size_t)1;
        }
        size_t MaxH = 0, tempH = 0, is = 1;
        subHeight(MaxH, tempH, root_, is);
        return MaxH;
    }
};



double get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}
int rand_uns(int min, int max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

int main(){
    //ios::sync_with_stdio(false); cin.tie(nullptr);
    RBTree<int> t;

    double start = 0, finish = 0;
    int n = 10000;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        a[i] = rand_uns(10000, 1000000);
    }
    start = get_time();
    for (size_t i = 0; i < (size_t)n; i++){
        t.insert(a[i]);
        if (t.size() != i+1){
            cout << "Failed insert! Size != " << i+1 << "\n";
            break;
        }
    }
    cout << "Size = " << t.size() << "\tHeight = " << t.height() << "\tBlackHeight = " << t.black_height() << "\n";
    for (size_t i = 0; i < (size_t)n; i++){
        if (t.find(a[i]) == NULL){
            cout << "Failed erase! Didn't find " << a[i] << "\n";
        }
        t.erase(a[i]);
        if (t.size() != n-i-1){
            cout << "Failed erase! Size != " << i+1 << "\n";
            break;
        }
    }
    if (t.size() != 0){
        cout << "Failed! Size != 0\n";
    }
    finish = get_time();
    cout << "Test sequence initialization: \t\t\t\t" << finish - start << endl;

    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    t.insert(6);
    t.erase(1);
    t.erase(2);
    t.erase(3);
    t.erase(4);
    t.erase(5);
    t.erase(6);

    start = get_time();
    for (int i = 1; i <= 100; i++){
        for (int j = 1; j <= i; j++){
            t.insert(j);
        }
        cout << "Size = " << t.size() << "\tHeight = " << t.height() << "\tBlackHeight = " << t.black_height() << "\n";
        for (int j = 1; j < i/2; j++){
            t.erase(j);
        }
        for (int j = 1; j < i/2; j++){
            t.insert(j);
        }
        for (int j = 1; j <= i; j++){
            t.erase(j);
        }
    }
    finish = get_time();
    cout << "Test sequence initialization: \t\t\t\t" << finish - start << endl;
    return 0;
}
