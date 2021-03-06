#include <bits/stdc++.h>

void convert_to_vec(const std::string & str, std::vector<int> & vec)
{
    std::stringstream stream(str);
    std::string segment;
    while(std::getline(stream,segment,' '))
    {
        vec.push_back(std::stoi(segment));
    }
}


int main(int argc, char ** argv)
{
    if (argc < 3)
    {
        std::cout << "./app input.txt output.txt" << std::endl;
        return 0;
    }

    std::ifstream  in(argv[1]);
    std::ofstream out(argv[2]);

    std::string xstring;
    std::string coststring;

    std::vector<int> x;
    std::vector<int> cost;

    int len = 0;
    int roadlen = 0;

    std::map<int,int> mp;
    std::map<int,std::vector<int>> set;

    std::getline(in,xstring);
    std::getline(in,coststring);

    convert_to_vec(xstring,x);
    convert_to_vec(coststring,cost);

    len = x.size();
    for (int i = 0; i < len; ++i)
    {
        mp[x[i]] = cost[i];
        //        mp[x[i+1]] = cost[i+1];
        //        mp[x[i+2]] = cost[i+2];
    }

    std::sort(x.begin(),x.end());
    std::vector<int> dp(x.size(),0);

    for (int i = 0; i < x.size();++i)
    {
        int k = i;
        while (k!=0 && x[i]-x[k]<5)
            k--;
        if (i > 0 && x[i]-x[k]>5)
        {
            dp[i] = std::max(dp[i-1],dp[k]+mp[x[i]]);
            if (dp[i] == dp[i-1])
            {
                set[i] = set[i-1];
            }
            else
            {
                auto subset = set[k];
                subset.push_back(x[i]);
                set[i] = subset;
            }
        }
        else
        {
            dp[i] = std::max(dp[i == 0 ? 0 : i-1],mp[x[i]]);
            if (i > 0 & dp[i] == dp[i-1])
            {
                set[i] = set[i-1];
            }
            else{
                std::vector<int> k;
                k.push_back(x[i]);
                set[i] = k;
            }
        }
    }

    out << dp[x.size()-1] << std::endl;
    auto nums = set[x.size() -1];
    for (auto & num : nums)
        out << num << " ";

    in.close();
    out.close();
}
