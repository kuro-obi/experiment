#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

class Solution {

    static bool insert_if( std::string& sub,  char c)
    {
        auto f = std::find_if(sub.begin(), sub.end(), [c](const char v){ return v == c; });
        if( f==sub.end())
        {
            sub.push_back(c);
            return true;
        }
        return false;
    }

    public:
    static int lengthOfLongestSubstring(const std::string& s) 
    {
        int first_pos_candidate = 0;
        std::vector< std::string > possibles;
        std::set<int> failed;
        possibles.resize(s.size());

        for(int sidx = 0; sidx < s.size() ; ++sidx)
        {
            for( int cidx = 0; cidx < sidx; ++cidx)
            {
                if( failed.find(cidx) == failed.end())
                {
                    if(not insert_if(possibles[cidx],s[sidx]))
                    {
                        failed.insert(cidx);
                    }
                }
            }
        }
        int max = 0;
        int max_idx = 0;
        for(int idx = 0; idx < possibles.size(); ++idx)
        {
            const auto& c = possibles[idx];
            if( c.size() > max)
            {
                max = c.size();
                max_idx = idx;
            }
        }
        std::cout<<"MAX substr:"<<max<<" "<<possibles[max_idx]<<std::endl;
        return max;
    }
};

int main(int argc, const char* argv[])
{

    std::cout<< Solution::lengthOfLongestSubstring("aaaaa")<<std::endl;
    std::cout<< Solution::lengthOfLongestSubstring("abcabcbb")<<std::endl;
    std::cout<< Solution::lengthOfLongestSubstring("pwwkew")<<std::endl;
}

