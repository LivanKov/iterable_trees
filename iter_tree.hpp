#include <stack>
#include <iostream>
#include <vector>
#include <variant>
#include <stack>


template <typename T>
class Tree
{

private:
    class Node
    {
    public:
        Node *left;
        Node *right;
        T val;

        Node(T data)
        {
            val = data;
            left = nullptr;
            right = nullptr;
        }
        Node()
        {
            val = 0;
            left = nullptr;
            right = nullptr;
        }
    };

    void flatten_type_1(std::vector<std::variant<T, char>> &tree_vals, Node *current, size_t index) const
    {
        if (current)
        {
            tree_vals[index] = current->val;
            flatten_type_1(tree_vals, current->left, index * 2 + 1);
            flatten_type_1(tree_vals, current->right, index * 2 + 2);
        }
    }

public:
    Node *root;

    size_t size;

    size_t height;

    Tree() : root{nullptr}, size{0}, height{0} {}
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Tree<U> &tree);

    void insert(int val)
    {
        Node *current = root;
        size_t current_height = 1;
        if (!current)
        {
            root = new Node(val);
            size++;
            height = current_height;
            return;
        }
        for (;;)
        {
            if (val > current->val && current->right)
            {
                current = current->right;
                current_height++;
            }
            else if (val < current->val && current->left)
            {
                current = current->left;
                current_height++;
            }
            else if (val > current->val && !current->right)
            {
                current->right = new Node(val);
                size++;
                if (current_height + 1 > height)
                    height = current_height + 1;
                break;
            }
            else if (val < current->val && !current->left)
            {
                current->left = new Node(val);
                size++;
                if (current_height + 1 > height)
                    height = current_height;
                break;
            }
        }
    }

    template<typename... Args>
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Tree<T> &tree)
{
    os << "[ ";
    std::vector<std::variant<T, char>> tree_vals((1 << tree.height) - 1, '-');
    tree.flatten_type_1(tree_vals, tree.root, 0);
    for (auto const &val : tree_vals)
    {
        try
        {
            os << std::get<T>(val) << " ";
        }
        catch (std::bad_variant_access const &e)
        {
            os << std::get<char>(val) << " ";
        }
    }
    return os << "]";
}