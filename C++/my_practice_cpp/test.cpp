#include <iostream>
#include <vector>  
using namespace std;
class Solution {
public:
    string minWindow(string s, string t) {
        int left = 0,right = 0;
        int distance = 0;
        int start = 0,result = s.length()+1;
        vector<int> minFreq(128,0);
        vector<int> tFreq(128,0);
        for(int i=0; i < t.length();i++)
        {
            tFreq[t[i]]++;
        }


        while(right < s.length())
        {
            
            if(tFreq[s[right]] ==0)
            {
                right++;
                continue;
            }
            //即将加入的字符是t中的，distance增加
            if(minFreq[s[right]] < tFreq[s[right]])
            {
                distance++;
            }
            minFreq[s[right]]++;
            right++;

            while(distance == t.length())//子字符串包含t中所有字符。
            {
                if(result > right-left)
                {
                    result = right-left;
                    start = left;
                }

                if(tFreq[s[left]] == 0)
                {
                    left++;
                    continue;
                }
                //即将抛弃的字符会使得子字符串不再覆盖t，distance--
                if(minFreq[s[left]] == tFreq[s[left]])
                {
                    distance--;
                }
                minFreq[s[left]]--;
                left++;
            }
        }
        if(result  == s.length()+1)
        {
            return "";
        }
        else
        {
            string sub = s.substr(start,result);
            return sub;
        }
    }
}; 
int main()
{
    string s = "cabwefgewcwaefgcf";
    string t = "cae";
    Solution sol;
    string result = sol.minWindow(s,t);
    cout <<result.length()<<endl;
    for(int i =0; i <result.length();i++)
    {
        cout << result[i];
    }
    cout <<endl;
    return 0;
}