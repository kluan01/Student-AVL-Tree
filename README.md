IDE: CLion  
Compiler: C++17

## Functionality of Commands
insert NAME ID - Add a Student object into the tree with the specified NAME & student ID.  
remove ID - Find and remove the account with the specified ID from the tree.  
search ID - Search for the student with the specified ID from the tree.  
search NAME - Search for the student in the tree with the specified NAME.  
removeInorder N - Remove the Nth student ID from the inorder traversal of the tree (N = 0 for the first item, etc).  
  
printInorder - self explanatory for following tree traversal commands    
printPreOrder  
printPostOrder  
printLevelCount  



## To Test:
1. Clone and download dependencies found in CMakeList
2. In the first line, name the number of lines/commands for the input
3. Name your command

Example Input: 
```
8
insert "Brandon" 45679999
insert "Brian" 35459999
insert "Briana" 87879999
insert "Bella" 95469999
printInorder
remove 45679999
removeInorder 2
printInorder
```

Example Output:
```
successful
successful
successful
successful
Brian, Brandon, Briana, Bella
successful
successful
Brian, Briana
```
