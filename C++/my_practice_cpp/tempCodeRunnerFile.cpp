#include <iostream>
#include <vector>  
using namespace std;
class Solution {
public:
    string minWindow(string s, string t) {
        int i=0,j=0,start=0,end=0,result = INT32_MAX;
        string sub="";
        for(j=0; j < s.length(); j++)
        {
            sub = sub+s[j];
            while(isInvolve(t,sub))
            {
                start = i;
                end = j;
                result = result < sub.length()?result:sub.length();
                sub.erase(0);
                i++;
            }
        }
        if(result==INT32_MAX)
        {
            return "";
        }
        else
        {
            string sub = s.substr(i,j-i+1);
            return sub;
        }
    }
    bool isInvolve(string t,string substring)
    {
        for(int i=0; i < t.length(); i++)
        {
            int find = substring.find(t[i]);
            if(find >= substring.length())
            {
                return false;
            }
            substring.erase(find);
        }
        return true;
    }
}; 
int main()
{
    string s = "ADOBECODEBANC";
    string t = "ABC";
    Solution sol;
    string result = sol.minWindow(s,t);
    for(int i =0; i <result.length();i++)
    {
        cout << result[i];
    }
    cout <<endl;
    return 0;
}