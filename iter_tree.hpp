#include <stack>
#include <iostream>
#include <vector>
#include <variant>
#include <stack>

template <typename T>
concept has_ostream = requires(T t, std::ostream &os) {
    { os << t } -> std::same_as<std::ostream &>;
};

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

    auto insert(T val) -> void
    {
        write_value(std::move(val));
    }

    template <typename... Args>
        requires std::constructible_from<T, Args...>
    auto emplace(Args &&...args)
    {
        write_value(T{std::forward<Args>(args)...});
    }

private:
    auto write_value(T &&val) -> void
    {
        if (!root)
        {
            root = new Node(val);
            height = 1;
            return;
        }
        size_t current_height{1};
        Node *current = root;
        while (current)
        {
            if (val < current->val && !(current->left))
            {
                current->left = new Node(val);
                current_height++;
                update_height(current_height);
                break;
            }
            if (val >= current->val && !(current->right))
            {
                current->right = new Node(val);
                current_height++;
                update_height(current_height);
                break;
            }
            current = val < current->val ? current->left : current->right;
            current_height++;
        }
    }

    auto update_height(size_t new_height) -> void
    {
        height = new_height > height ? new_height : height;
    }
};

template <typename T>
    requires has_ostream<T>
std::ostream &operator<<(std::ostream &os, const Tree<T> &tree)
{
    std::cout << "check1" << std::endl;
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