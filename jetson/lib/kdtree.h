/* \author Aaron Brown */
// Quiz on implementing kd tree

#if !defined(KDTREE_H)
#define KDTREE_H

#include <vector>
#include <math.h> 

// Structure to represent node of kd tree
struct Node {
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree {
	Node* root;

	KdTree()
	: root(NULL)
	{}

	void insertHelper(Node **node, uint depth, std::vector<float> point, int id) {
	    // If tree is empty
	    if (nullptr == *node) {
	        *node = new Node(point, id);
	    }
	    else {
	        // Calculate current dimension
	        uint current_dimension = depth % 2;

	        if (point[current_dimension] < ((*node)->point[current_dimension])) {
                insertHelper(&((*node)->left), depth + 1, point, id);
	        }
	        else {
                insertHelper(&((*node)->right), depth + 1, point, id);
	        }
	    };
	}


	void insert(std::vector<float> point, int id) {
		// the function should create a new node and place correctly with in the root 
        insertHelper(&root, 0, point, id);
	}


    void searchHelper(std::vector<float> target, Node* node, int depth, float distanceTol, std::vector<int>& ids) {
        if (nullptr != node) {
            float dx = fabs(node->point[0] - target[0]);
            float dy = fabs(node->point[1] - target[1]);

            if (dx <= distanceTol && dy <= distanceTol) {
                float distance = std::hypotf(dx, dy);
                if (distance <= distanceTol) {
                    ids.push_back((node->id));
                }
            }

            // Check across boundary
            if ((target[depth % 2] - distanceTol) < node->point[depth % 2]) {
                searchHelper(target, node->left, depth + 1, distanceTol, ids);
            }
            if ((target[depth % 2] + distanceTol) > node->point[depth % 2]) {
                searchHelper(target, node->right, depth + 1, distanceTol, ids);
            }
        }
	}


	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol) {
		std::vector<int> ids;
		searchHelper(target,  root, 0, distanceTol, ids);
		return ids;
	}
};


#endif // KDTREE_H

