{
#include <bits/stdc++.h>
    using namespace std;
    struct Node
    {
        int data;
        struct Node *left;
        struct Node *right;
        int height;
        friend std::ostream &operator<<(std::ostream &, const Node &);
    };
    int heigh(struct Node * Node)
    {
        /* base case tree is empty */
        if (Node == NULL)
            return 0;

        /* If tree is not empty then height = 1 + max of left
      height and right heights */
        return 1 + max(heigh(Node->left), heigh(Node->right));
    }
    bool isBalanced(struct Node * root)
    {
        int lh; /* for height of left subtree */
        int rh; /* for height of right subtree */

        /* If tree is empty then return true */
        if (root == NULL)
            return 1;

        /* Get the height of left and right sub trees */
        lh = heigh(root->left);
        rh = heigh(root->right);

        if (abs(lh - rh) <= 1 &&
            isBalanced(root->left) &&
            isBalanced(root->right))
            return 1;

        /* If we reach here then tree is not height-balanced */
        return 0;
    }

    /* UTILITY FUNCTIONS TO TEST isBalanced() FUNCTION */

    /* returns maximum of two integers */

    /*  The function Compute the "height" of a tree. Height is the
    number of Nodes along the longest path from the root Node
    down to the farthest leaf Node.*/
    int _B_(Node * root)
    {
        if (root == NULL)
            return 0;
        int lH = _B_(root->left);
        if (lH == -1)
            return -1;
        int rH = _B_(root->right);
        if (rH == -1)
            return -1;
        if (abs(lH - rH) > 1)
            return -1;
        return max(lH, rH) + 1;
    }
    bool _B(Node * root)
    {
        if (_B_(root) == -1)
            return false;
        else
            return true;
    }
    bool I_(Node * root)
    {
        static struct Node *prev = NULL;

        if (root)
        {
            if (!I_(root->left))
                return false;

            if (prev != NULL && root->data <= prev->data)
                return false;

            prev = root;

            return I_(root->right);
        }

        return true;
    }
    Node *insertToAVL(Node * Node, int data);
    vector<int> z;
    void inorder(Node * root)
    {
        //	z.clear();
        if (root == NULL)
            return;
        {
            inorder(root->left);
            z.push_back(root->data);
            inorder(root->right);
        }
    }
    /* Drier program to test above function*/
    int main()
    {
        int t;
        cin >> t;
        while (t--)
        {
            int q;
            cin >> q;
            Node *root = NULL;
            bool f = true;
            vector<int> a;
            while (q--)
            {
                int k;
                cin >> k;
                a.push_back(k);
                root = insertToAVL(root, k);
                if (!isBalanced(root))
                {
                    f = false;
                    break;
                }
            }

            z.clear();

            inorder(root);

            set<int> s(a.begin(), a.end());
            vector<int> zz(s.begin(), s.end());
            if (z.size() != zz.size())
                f = false;
            else
            {
                for (int i = 0; i < z.size(); i++)
                {
                    if (z[i] != zz[i])
                        f = false;
                }
            }
            if (f)
                cout << 1 << endl;
            else
                cout << 0 << endl;
        }
        return 0;


    /*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

    /* The structure of the Node is
struct Node
{
    int data;
    Node *left;
    Node *right;
    int height;
};
*/
    /*You are required to complete this method */
    ostream &operator<<(ostream &os, const Node &N)
    {
        static int i = 0;
        // static Node * left = 0, * right = 0;
        // if (&N == left || &N == right)
        //     i++;
        // else
        //     i = --i >= 0 ? i : 0;    
        // left = N.left;
        // right = N.right;
        
        os << std::string(i, ' ') << "data: " << N.data << "\n"
           << std::string(i, ' ') << "height: " << N.height << "\n";
           if (N.left) {i+=2;os << std::string(i-2, ' ') << "left: {\n" << *N.left << std::string(i-2, ' ') << "}\n";i-=2;}
           if (N.right) {i+=2;os << std::string(i-2, ' ') << "right: {\n" << *N.right << std::string(i-2, ' ') << "}\n";i-=2;}
        //   if (N.left) {os << "left: " << 0 << "\n";}
        // if (N.left) { << "right: " << *N.right;
        // if (!N.left && !N.right) {i = i-=2 >= 0 ? i : 0;}
        // i = i-=2 >= 0 ? i : 0;
        return os;
    }
    
    
    Node *insertToAVL(Node * node, int data)
    {
    // static Node * insertedNode;
        if (!node)
            return new Node{data, 0, 0, 1};

if (data == node->data) {
    return node;
}
        Node **nextNode = data < node->data ? &node->left : &node->right;
        // Node *nextNode = curNode->data < curNode->left->data ? curNode->left : curNode->right;
        *nextNode = insertToAVL(*nextNode, data);
        //nextNode =  *newNode;
        int lh = node->left ? node->left->height : 0;
        int rh = node->right ? node->right->height : 0;
        node->height = max(lh,rh) + 1;
        cout << "This node:\nlh: " << lh << "\nrh: " << rh << "\n"
             << *node << "" << endl;
        cout << "Next Node:\ndata: " << (*nextNode)->data << "\nheight: " << (*nextNode)->height << "\n__________\n" << endl;
        // cout << "data: "<< node->data << "\nlh: "<< lh << "\nrh: "<< rh << "" << endl << endl;
        if (abs(lh-rh) > 1) {
            Node **[] thisChild = {&(node->left),&(node->right)}
            Node **[] nextChild = {&((*nextNode)->left),&((*nextNode)->right)}
            Node **[] grandChild = 
            int LR = !(thisChild[1] == nextNode);
            // Node * grandchild = nextNode
            Node * node1 = *nextNode;
            *(nextChild[LR]) = node;
            *nextNode = *(nextChild[LR]);
            node1 -> height = heigh(node1);
            node->height = heigh(node);
            
                // LR2 = !!(*thisChild[0]);
                
            
            
            // Node *[] datas = {insertedNode,node,*nextNode};
            // std::vector<Node *> nodes = (datas,datas+3);
            // std::sort(nodes,nodes+3,[](Node * n, Node * n2){
            //     return (n->data < n2-> data);
            // })
            // int nodePosition = std::distance(nodes,std::find(nodes,nodes+3,insertedNode))
            // switch (nodePosition) {
            //     case 0:
            //         n
            //     case 2:
            //     case 1:
                    
            }
        }

        node->height = heigh(node);
        cout << "__________" << data << "__________" << endl
             << endl;
        return node;
    }