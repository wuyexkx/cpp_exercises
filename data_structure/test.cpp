#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;


vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
{
    vector<int> intersection;
    unordered_set<int> hashset;
    for(int v : nums1) hashset.insert(v);
    for(int v : nums2) hashset.insert(v);
    
    for(int i = 0, auto it=hashset.begin(); it!=hashset.end(); it++, i++)
        intersection[i] = *it;
    return intersection;
}


int main()
{
    
    unordered_map<char , int> map;
    for(auto c : map)
    {
        c.fi
    }

}