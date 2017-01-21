#include <bits/stdc++.h>
#include <iostream> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <typeinfo>
#include <string>
using namespace std;
 
const int k = 2;
 
// A structure to represent node of kd tree
struct Node
{
    double point[k]; // To store k dimensional point
    //vector<double> point; // To store k dimensional point
    //point.assign(2,0);
    Node *left, *right;
    //vector < vector <int>>;     // To store
};
 
// A method to create a node of K D tree
struct Node* newNode(double arr[])
//struct Node* newNode( vector<double> arr)
{
    struct Node* temp = new Node;
 
    for (int i=0; i<k; i++)
       temp->point[i] = arr[i];
 
    temp->left = temp->right = NULL;
    return temp;
}
 
// Inserts a new node(point[]) ,and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node *insertRec(Node *root, double point[], unsigned depth)
//Node *insertRec(Node *root, vector<double> point , unsigned depth)
{
    // Tree is empty?
    if (root == NULL)
       return newNode(point);
 
    // Calculate current dimension (cd) of comparison
    unsigned cd = depth % k;
 
    // Compare the new point with root on current dimension 'cd'
    // and decide the left or right subtree
    if (point[cd] < (root->point[cd]))
        root->left  = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);
 
    return root;
}
 
// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
Node* insert(Node *root, double point[])
//Node* insert(Node *root, vector<double> point)
{
    return insertRec(root, point, 0);
}



// A utility method to determine if two Points are same
// in K Dimensional space
bool arePointsSame(double point1[], double point2[])
//bool arePointsSame(vector<double> point1, vector<double> point2)
{
    // Compare individual pointinate values
    for (int i = 0; i < k; ++i)
        if (point1[i] != point2[i])
            return false;
 
    return true;
}



// A utility function to find minimum of three integers
Node *minNode(Node *x, Node *y, Node *z, int d)
{
    Node *res = x;
    if (y != NULL && y->point[d] < res->point[d])
       res = y;
    if (z != NULL && z->point[d] < res->point[d])
       res = z;
    return res;
}
 
// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
Node *findMinRec(Node* root, int d, unsigned depth)
{
    // Base cases
    if (root == NULL)
        return NULL;
 
    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;
 
    // Compare point with root with respect to cd (Current dimension)
    if (cd == d)
    {
        if (root->left == NULL)
            return root;
        return findMinRec(root->left, d, depth+1);
    }
 
    // If current dimension is different then minimum can be anywhere
    // in this subtree
    return minNode(root,
               findMinRec(root->left, d, depth+1),
               findMinRec(root->right, d, depth+1), d);
}
 
// A wrapper over findMinRec(). Returns minimum of d'th dimension
Node *findMin(Node* root, int d)
{
    // Pass current level or depth as 0
    return findMinRec(root, d, 0);
}
 

// Copies point p2 to p1
void copyPoint(double p1[], double p2[])
{
   for (int i=0; i<k; i++)
       p1[i] = p2[i];
}

// Delete a Point represented by "point[]" in the K D tree (whose root is *root).
// The parameter depth is used to determine current axis.
Node *deleteNodeRec(Node *root, double point[], int depth)
{
    // Given point is not present
    if (root == NULL)
        return NULL;
 
    // Find dimension of current node
    int cd = depth % k;
 
    // If the point to be deleted is present at root
    if (arePointsSame(root->point, point))
    {
        // 2.b) If right child is not NULL
        if (root->right != NULL)
        {
            // Find minimum of root's dimension in right subtree
            Node *min = findMin(root->right, cd);
 
            // Copy the minimum to root
            copyPoint(root->point, min->point);
 
            // Recursively delete the minimum
            root->right = deleteNodeRec(root->right, min->point, depth+1);
        }
        else if (root->left != NULL) // same as above
        {
            Node *min = findMin(root->left, cd);
            copyPoint(root->point, min->point);
            root->right = deleteNodeRec(root->left, min->point, depth+1);
        }
        else // If node to be deleted is leaf node
        {
            delete root;
            return NULL;
        }
        return root;
    }
 
    // 2) If current node doesn't contain point, search downward
    if (point[cd] < root->point[cd])
        root->left = deleteNodeRec(root->left, point, depth+1);
    else
        root->right = deleteNodeRec(root->right, point, depth+1);
    return root;
}
 
// Function to delete a given point from K D Tree with 'root'
// It mainly uses above recursive
// function "deleteNodeRec()"
 Node* deleteNode(Node *root, double point[])
{
   // Pass depth as 0
   return deleteNodeRec(root, point, 0);
}



 
// Searches a Point represented by "point[]" in the K D tree.
// The parameter depth is used to determine current axis.
bool searchRec(Node* root,double point[], unsigned depth)
//bool searchRec(Node* root,vector<double> point, unsigned depth)
{
    // Base cases
    if (root == NULL)
        return false;
    if (arePointsSame(root->point, point))
        return true;
 
    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;
 
    // Compare point with root with respect to cd (Current dimension)
    if (point[cd] < root->point[cd])
        return searchRec(root->left, point, depth + 1);
 
    return searchRec(root->right, point, depth + 1);
}
 
// Searches a Point in the K D tree. It mainly uses
// searchRec()
bool search(Node* root, double point[])
//bool search(Node* root, vector<double> point)
{
    // Pass current depth as 0
    return searchRec(root, point, 0);
}
 


//////////////////////////////////////////////////////////////
// range 2*2  first row x second row y
// store all the points in range into the vector xxx
void RangeSearchRec (vector<Node*> *xxx, Node* root, double range[][2], unsigned depth , int *counts )
{ 
    if (root == NULL)
    {
    	return;
    }
    
    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k ;
    unsigned cd2 = (depth+1) % k; 


    if (( (range[cd][0] < root->point[cd] )&& (root->point[cd]<  range[cd][1] )) &&  ( (range[cd2][0] < root->point[cd2]) && (root->point[cd2] <range[cd2][1]) ))
    {
    	cout<< root->point[0]<<root->point[1]<<endl ;
    	xxx->push_back ( root ) ;
        counts += 1 ;
    }

 
    if ( root->point[cd]  <  range[cd][0] )
    	RangeSearchRec(xxx, root-> right, range, depth +1 ,counts ) ;
    else if ( root->point[cd] > range[cd][1] )
    	RangeSearchRec(xxx, root-> left , range, depth +1 , counts) ;
    else if ( (range[cd][0] < root->point[cd] )&& (root->point[cd]<  range[cd][1] ) )
    {
        RangeSearchRec(xxx, root-> right, range, depth +1 , counts ) ;
        RangeSearchRec(xxx, root-> left , range, depth +1 , counts ) ;
    }

    /*    
    std::vector<Node*>::iterator it;
    for( it = xxx->begin(); it != xxx->end(); it++ ) 
    {
    	cout<<"from vnode";
    	cout << (*it)->point[0] <<","<<(*it)->point[1] <<endl;
    }
    */
}

// Nearest Neighbor search 
// store the nearest point in NNs 
Node* NNS( Node *NNs, double CND ,Node *root, double point[], unsigned depth)
{
    // Tree is empty?
    if (root == NULL)
    {
        return NNs;  ////
    }
    // Calculate current dimension (cd) of comparison
    unsigned cd = depth % k;
    unsigned cd2 = (depth+1) % k;
    
    ///compare the diatance with the current nearest one;
    //double CurrentNearDist = 100;
    double dist = 0;
    double ele1 = 0;
    ele1 = ( point[cd] - root->point[cd] );
    double ele2 = 0;
    ele2 = ( point[cd2] - root->point[cd2] );
    dist = sqrt( pow(ele1,2) + pow(ele2,2) ) ;
    if ( dist < CND )
    {   
        CND = dist ;
	NNs = root ;  
    }
    // Compare the new point with root on current dimension 'cd'
    // and decide the left or right subtree
    if ( point[cd] < (root->point[cd]) )
        NNs = NNS( NNs , CND , root->left, point, depth + 1);
    else
    {
        NNs = NNS( NNs , CND , root->right, point, depth + 1);
    }
    return NNs;
}





int main()
{

    struct Node *root = NULL;

/*
    // start of counting the running time to build a 2d-tree on N random points in the unit square
    int N = 0 ;
    cout << "Give the running time in seconds to build a 2d-tree on N random points in the unit square : " << endl;
    cout << "please decide N : ";
    cin >> N;
 
    const clock_t begin_time = clock();   //  start count time    
    for(int i = 0; i < N; ++i)
    {
        double* points = new double[k];
	points[0] = rand();
	points[1] = rand();
        root = insert(root, points);
        delete [] points; 
    }
    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    cout<< endl;
*/
    

    // start of parsing file to build a 2d tree
    int linenumber = -1 ; 
    string readLine; 
    ifstream txtfile("input1M.txt");
    
    //const clock_t begin_time = clock();   //  start count time    
    while ( getline (txtfile,readLine) ) // read line by line
    {   
        double* points = new double[k];
        linenumber +=1 ;
        std::string s = readLine ;
        std::string delimiter = " ";
        std::string token = s.substr(0, s.find(delimiter)); 
        double d1 = strtod( token.c_str(), NULL ) ;
        s.erase(0, s.find(delimiter) + delimiter.length());
        std::string token1 = s.substr(0); 
        double d2 = strtod( token1.c_str(), NULL ) ;
        
	points[0] = d1 ;   // x coordinate
        points[1] = d2 ;   // y coordinate

        root = insert(root, points);
        delete [] points; 
        
    }
    //cout << "the running time inserting the nodes in the file is : " ;
    //std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    cout<<endl;


// cout << "example code to perform delete operation : " << endl;
/*
    cout << root->point[0] << ", " << root->point[1] << endl;
    double deletepoint[2] = {0.042191,0.783317};
    root = deleteNode(root, deletepoint );
    cout << "Root after deletion \n";
    cout << root->point[0] << ", " << root->point[1] << endl;
*/




    ///////range search 
    double x1,y1,x2,y2,x3,y3,x4,y4 ; 
    cout<< " Start of Range Search : " << endl ; 
    cout<< " Enter the x coordinate of the first point : " ;
    cin >> x1 ;
    cout<< " Enter the y coordinate of the first point : " ;
    cin >> y1 ;
    cout<< " Enter the x coordinate of the second point : " ;
    cin >> x2 ;
    cout<< " Enter the y coordinate of the second point : " ;
    cin >> y2 ;
    cout<< " Enter the x coordinate of the third point : " ;
    cin >> x3 ;
    cout<< " Enter the y coordinate of the third point : " ;
    cin >> y3 ;
    cout<< " Enter the x coordinate of the fourth point : " ;
    cin >> x4 ;
    cout<< " Enter the y coordinate of the fourth point : " ;
    cin >> y4 ;
    double range1[2][2];
    if (x1==x2)
    {
        range1[0][0] = x1 ;
        range1[0][1] = x3 ;
        if (y1<y2)
        {
            range1[1][0] = y1 ; 
            range1[1][1] = y2 ;
        }
        else 
        {
            range1[1][0] = y2 ; 
            range1[1][1] = y1 ;
        }
    } 
    else if (x1==x3)
    {
        range1[0][0] = x1 ;
        range1[0][1] = x2 ;
        if (y1<y3)
        {
            range1[1][0] = y1 ; 
            range1[1][1] = y3 ;
        }
        else 
        {
            range1[1][0] = y3 ; 
            range1[1][1] = y1 ;
        }
    } 
    else if (x1==x4)
    {
        range1[0][0] = x1 ;
        range1[0][1] = x2 ;
        if (y1<y4)
        {
            range1[1][0] = y1 ; 
            range1[1][1] = y4 ;
        }
        else 
        {
            range1[1][0] = y4 ; 
            range1[1][1] = y1 ;
        }
    } 
    else 
        cout<<"return error " ; 

    int counts = 0 ;
    vector<Node*> xxx;
    RangeSearchRec(&xxx, root, range1,0, &counts );

    std::vector<Node*>::iterator it;
    cout<<"These are the points in the range : " << endl ;
    for( it = xxx.begin(); it !=xxx.end(); it++ ) 
    {
    	cout << (*it)->point[0] <<","<<(*it)->point[1] <<endl;
    }
    cout << " Above are the points in the range . " <<endl;
    cout << " Number of points in the range : " << xxx.size() << endl ;
   
 
    /// NNs

    cout << "Start of Nearest Neighbor Search : " << endl ;
    double x,y ; 
    cout << "please input the x coordinate of search point  : " ;
    cin >> x ; 
    cout << "please input the y coordinate of search point  : " ;
    cin >> y ; 

    double point1[]= { x , y };

    
    const clock_t begin_time = clock();   //  start count time    
    struct Node *NNs; 
    NNs = NNS ( NNs , 100 , root, point1 , 0 );   // 100 is just to initialize the current nearest distance 
    cout << "the running time of nearest neighbor operation is : ";
    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    cout<< endl ;
    cout << "This is the nearest point of (" <<x << ","<< y <<") : " <<endl ; 
    cout << NNs->point[0] <<"," << NNs->point[1] <<endl;
    return 0;
///////////////////////////////////////restart 
}

