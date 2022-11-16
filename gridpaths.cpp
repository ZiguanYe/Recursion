#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
// for pair
#include <functional>
#include <string>

using namespace std;

// typedef for X,Y pair
typedef std::pair<size_t, size_t> XYPair;

// Utility Prototypes
bool operator==(const XYPair& p1, const XYPair& p2);
void printPaths(const std::vector<std::vector<XYPair> >& results);

// Utility function to compare XY points
bool operator==(const XYPair& p1, const XYPair& p2)
{
  return p1.first == p2.first && p1.second == p2.second;
}


// Primary street grid function prototype
std::vector<std::vector<XYPair> > gridpaths(const XYPair& inter, const XYPair& final);

// Prototype any helper functions here
void gridpathsHelper(const XYPair& inter, const XYPair& final, XYPair curr, std::vector<XYPair> path, std::vector<std::vector<XYPair> > &result);




// Implement your gridpaths and any helper functions below
std::vector<std::vector<XYPair> > gridpaths(
    const XYPair& inter, 
    const XYPair& final)
{
    std::vector<std::vector<XYPair>> result;
    std::vector<XYPair> path;
    XYPair start = make_pair(0,0);
    
    if(start == inter && start == final)
    {
        //path.push_back(start);
        //result.push_back(path);
        return result;
    }
    
    gridpathsHelper(inter, final, start, path, result);
    printPaths(result);
    return result;
}

void gridpathsHelper(const XYPair& inter, const XYPair& final, XYPair curr, std::vector<XYPair> path, std::vector<std::vector<XYPair>>& result)
{
    cout<< curr.first << "," << curr.second << endl;
    path.push_back(curr);
    
    if(curr == final)
    {
        result.push_back(path);
    }
    else if(curr.first>final.first || curr.second>final.second)
    {
        return;
    }
    //havent been to inter
    else if(curr.first<inter.first && curr.second<inter.second)
    {
        XYPair curr1 = curr;
        curr1.first++;
        XYPair curr2 = curr;
        curr2.second++;
        //cout << "condition 1 passed" << endl;
        gridpathsHelper(inter, final, curr1, path, result);
        gridpathsHelper(inter, final, curr2, path, result);
    }
    //y-coordinate reached but x is not
    else if(curr.first<inter.first && curr.second==inter.second)
    {
        XYPair curr1 = curr;
        curr1.first++;
        //cout << "condition 2 passed" << endl;
        gridpathsHelper(inter, final, curr1, path, result);
    }
    //x-coordinate reached but y is not
    else if(curr.first==inter.first && curr.second<inter.second)
    {
        XYPair curr2 = curr;
        curr2.second++;
        //cout << "condition 3 passed" << endl;
        gridpathsHelper(inter, final, curr2, path, result);
    }
    //reach the inter, now go to final
    else
    {
        if(curr.first<final.first && curr.second<final.second)
        {
            XYPair curr1 = curr;
            curr1.first++;
            XYPair curr2 = curr;
            curr2.second++;
            //cout << "condition 4 passed" << endl;
            gridpathsHelper(inter, final, curr1, path, result);
            gridpathsHelper(inter, final, curr2, path, result);
        }
        //y-coordinate reached but x is not
        else if(curr.first<final.first && curr.second==final.second)
        {
            XYPair curr1 = curr;
            curr1.first++;
            //cout << "condition 5 passed" << endl;
            gridpathsHelper(inter, final, curr1, path, result);
        }
        //x-coordinate reached but y is not
        else if(curr.first==final.first && curr.second<final.second)
        {
            XYPair curr2 = curr;
            curr2.second++;
            //cout << "condition 6 passed" << endl;
            gridpathsHelper(inter, final, curr2, path, result);
        }
    }
}


// Complete - but can be changed for debugging purposes
int main(int argc, char* argv[])
{
  // Default to intermediate point of 2,3 and final location of 3,4
  size_t ix = 2, iy = 3, fx = 3, fy = 4;
  if(argc >= 5) {
    ix = atoi(argv[1]);
    iy = atoi(argv[2]);
    fx = atoi(argv[3]);
    fy = atoi(argv[4]);
  }
  vector<vector<XYPair> > results;
  results = gridpaths({ix,iy},{fx,fy});  
  printPaths(results);

  return 0;
}

// Prints the results in a clean fashion for human consumption / debugging
void printPaths(const vector<vector<XYPair> >& results)
{
  for( const auto& path : results) {
    for( size_t i = 0; i < path.size()-1; i++ ) 
    {      
      cout << path[i].first << "," << path[i].second << " -> ";
    }
    cout << path.back().first << "," << path.back().second << endl;
  }
  cout << results.size() << " solutions." << endl;

}
