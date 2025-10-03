#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int Values;
    struct Node* Right;
    struct Node* Left;
} Node;

typedef struct BinTree {
    Node* Central;
} BinTree;

Node* NewNode(int value);
bool Insert(BinTree* t, int value);
Node* Search(BinTree* t, int value);
bool Delete(BinTree* t, int value);

int main() {
    int choise;
    BinTree tree;
    tree.Central = NULL;
    int bufer;

    while (1) {
        printf("Выберите действие:\n");
        printf("1 - создать узел\n");
        printf("2 - удалить узел\n");
        printf("3 - найти узел\n");
        if (scanf("%d", &choise) != 1) {
            while(getchar() != '\n'); // clear input buffer
            continue;
        }

        switch (choise) {
            case 1:
                printf("укажите значение\n");
                if (scanf("%d", &bufer) != 1) {
                    while(getchar() != '\n');
                    break;
                }
                printf("%s\n", Insert(&tree, bufer) ? "true" : "false");
                break;
            case 2:
                printf("укажите значение\n");
                if (scanf("%d", &bufer) != 1) {
                    while(getchar() != '\n');
                    break;
                }
                printf("%s\n", Delete(&tree, bufer) ? "true" : "false");
                break;
            case 3:
                printf("укажите значение\n");
                if (scanf("%d", &bufer) != 1) {
                    while(getchar() != '\n');
                    break;
                }
                
                Node* found = Search(&tree, bufer);
                if (found != NULL) {
                    printf("Found node with value: %d\n", found->Values);
                    printf("Left child: %p\n", (void*)found->Left);
                    printf("Right child: %p\n", (void*)found->Right);
                } else {
                    printf("Node not found\n");
                }
                break;
            default:
                printf("За меня придурка не держи\n");
                break;
        }
    }

    return 0;
}

Node* NewNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->Values = value;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

bool Insert(BinTree* t, int value) {
    Node* newNode = NewNode(value);

    if (t->Central == NULL) {
        t->Central = newNode;
        return true;
    }

    Node* current = t->Central;
    Node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (value < current->Values) {
            current = current->Left;
        } else {
            current = current->Right;
        }
    }

    if (value < parent->Values) {
        parent->Left = newNode;
    } else {
        parent->Right = newNode;
    }

    return true;
}

Node* Search(BinTree* t, int value) {
    Node* tree = t->Central;

    while (tree != NULL) {
        if (value == tree->Values) {
            return tree;
        } else if (value < tree->Values) {
            tree = tree->Left;
        } else {
            tree = tree->Right;
        }
    }
    return NULL;
}

bool Delete(BinTree* t, int value) {
    if (t->Central == NULL) {
        return false;
    }

    Node* parent = NULL;
    Node* current = t->Central;
    bool is_minimal = false;

    //
    while (current != NULL && current->Values != value) {
        parent = current;
        if (value < current->Values) {
            is_minimal = true;
            current = current->Left;
        } else {
            is_minimal = false;
            current = current->Right;
        }
    }

    if (current == NULL) {
        return false; // Node not found
    }

    
    if (current->Left == NULL) {
        if (parent == NULL) {
            t->Central = current->Right;
        } else {
            if (is_minimal) {
                parent->Left = current->Right;
            } else {
                parent->Right = current->Right;
            }
        }
        free(current);
    } else if (current->Right == NULL) {
        if (parent == NULL) {
            t->Central = current->Left;
        } else {
            if (is_minimal) {
                parent->Left = current->Left;
            } else {
                parent->Right = current->Left;
            }
        }
        free(current);
    } else {
        Node* minimalnodeparent = current;
        Node* minimalnode = current->Right;

        while (minimalnode->Left != NULL) {
            minimalnodeparent = minimalnode;
            minimalnode = minimalnode->Left;
        }

        current->Values = minimalnode->
        if (minimalnodeparent == current) {
            minimalnodeparent->Right = minimalnode->Right;
        } else {
            minimalnodeparent->Left = minimalnode->Right;
        }
        free(minimalnode);
    }

    return true;
}
