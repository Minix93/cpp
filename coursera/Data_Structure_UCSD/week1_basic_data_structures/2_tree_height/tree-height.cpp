#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};

// int calculate_height(Node node){
//   int height {1};
//   if (node.children.empty()){
//     return height;
//   }else{
//     //calculate the height of each child node, and set the height to 1+highest
//     int highest {0};
//     for (auto child : node.children){
//       int h {0};
//       h = calculate_height(*child);
//       if (h > highest){
//         highest = h;
//       }
//     }
//     height += highest;
//   }
//   return height;
// }



int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  Node nodes[n];
  for (int i {0}; i < n; ++i){
    nodes[i] = Node();
  }
  int root {0};
  for (int child_index {0}; child_index < n; child_index ++){
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0){
      nodes[child_index].setParent(&nodes[parent_index]);
    }else{
      root = child_index;
    }
    nodes[child_index].key = child_index;
  }
  
  std::queue <Node> q;
  int num_current_level {0};
  int num_next_level {0};
  int height {0};
  

  q.push(nodes[root]);
  height = 0;
  num_current_level = 1;
  while (!q.empty())
  {
    if (!q.front().children.empty())
    {
      for (auto child : q.front().children){
        q.push(*child);
        num_next_level += 1;
      }
    }
    q.pop();
    num_current_level -= 1;
    if (num_current_level == 0)
    {
      height += 1;
      num_current_level = num_next_level;
      num_next_level = 0;
    }
    
  }
  

  // int height = calculate_height(nodes[root]);
  std::cout << height << std::endl;
  
  return 0;
}



int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
