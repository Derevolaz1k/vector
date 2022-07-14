#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <random>
#include <fstream>

class Beast
{
public:
    Beast(int id, std::string name, bool solidity, double weigth) :id(id), name(name), solidity(solidity), weigth(weigth){}//тривиальный коструктор
    Beast() :Beast(0, "", false, 0) {}
//private:
    int id;
    std::string name;
    bool solidity;
    double weigth;
};

struct maximums
{
    int max1=0;
    int max2=0;
    int max3=0;
};

struct minimums
{
    int min1 = 0;
    int min2 = 0;
    int min3 = 0;
};

std::string randName()
{
    std::ifstream file("names.txt");
    std::string str;
    for (int i = 0; i < rand() % 13+1; i++) 
    {
        std::getline(file, str);
    }
    file.close();
    return str;
}

int main()
{
    srand(time(NULL));
    std::vector<Beast> circus;
    circus.reserve(100);
    for (int i = 0; i < circus.capacity(); i++)
    {
        circus.emplace_back(i, randName(), rand() % 2 , (double)(rand()) / RAND_MAX * (20.0 - 7.0) + 7.0);
    }
    std::for_each(circus.begin(),circus.end(),[](Beast& arg) {std::cout << arg.id<< "\t\t" <<arg.name<< "\t\t" <<arg.solidity<< "\t\t" <<arg.weigth << '\n'; });

    std::shuffle(circus.begin(), circus.end(), std::random_device());
    std::cout << "\n\n\n";
    std::for_each(circus.begin(), circus.end(), [](Beast& arg) {std::cout << arg.id << "\t\t" << arg.name << "\t\t" << arg.solidity << "\t\t" << arg.weigth << '\n'; });
    std::sort(circus.begin(), circus.end(), [](Beast id1, Beast id2) {return id1.id < id2.id; });
    std::cout << "\n\nSort id\n\n";
    std::for_each(circus.begin(), circus.end(), [](Beast& arg) {std::cout << arg.id << "\t\t" << arg.name << "\t\t" << arg.solidity << "\t\t" << arg.weigth << '\n'; });
    std::sort(circus.begin(), circus.end(), [](Beast weigth1, Beast weigth2) {return weigth1.weigth < weigth2.weigth; });
    std::cout << "\n\nSort weigth\n\n";
    std::for_each(circus.begin(), circus.end(), [](Beast& arg) {std::cout << arg.id << "\t\t" << arg.name << "\t\t" << arg.solidity << "\t\t" << arg.weigth << '\n'; });
    std::sort(circus.begin(), circus.end(), [](Beast name1, Beast name2) { return name1.name.size() < name2.name.size(); });
    std::cout << "\n\nSort name\n\n";
    std::for_each(circus.begin(), circus.end(), [](Beast& arg) {std::cout << arg.id << "\t\t" << arg.name << "\t\t" << arg.solidity << "\t\t" << arg.weigth << '\n'; });
    maximums searchMax;
    
    std::for_each(circus.begin(), circus.end(), [&searchMax](Beast& arg)
        {
            if (searchMax.max1 < arg.id)
            {
                searchMax.max3 = searchMax.max2;
                searchMax.max2 = searchMax.max1;
                searchMax.max1 = arg.id;
            }
        });
    minimums searchMin;
    searchMin.min1 = searchMax.max1;
    searchMin.min2 = searchMin.min1;
    searchMin.min3 = searchMin.min1;
    std::for_each(circus.begin(), circus.end(), [&searchMin](Beast& arg)
        {
            if (searchMin.min1 > arg.id)
            {
                searchMin.min3 = searchMin.min2;
                searchMin.min2 = searchMin.min1;
                searchMin.min1 = arg.id;
            }
        });


    std::cout << "\n\n\n" <<"3 Maximum\t" << searchMax.max1 << '\t' << searchMax.max2 << '\t' << searchMax.max3;
    std::cout << "\n\n\n" <<"3 Minimum\t" << searchMin.min3 << '\t' << searchMin.min2 << '\t' << searchMin.min1<< "\n\n\n";
    int num = 50;
    auto res = std::find_if(circus.begin(), circus.end(), [&num](const Beast& arg)->bool
        {
            if (arg.id == num)
                return true;
            return false;
        }
    );
    if (res != circus.end())
        std::cout << "Number "<<num<<" found\n\n\n";

    else
        std::cout << "Number " << num << "  not found\n\n\n";
    return 0;
}
