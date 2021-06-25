#include "CTjson.h"

#include <vector>
#include <map>

using namespace CTjson;
using namespace std;

#define KVP(var) #var, var

struct Province {
  string name;
  vector<string> cities;

  ojsonstream &print(ojsonstream &ojs) const
  {
    return prt_obj(ojs, KVP(name), KVP(cities));
  }
};

struct Country {
  string name;
  vector<Province> provinces;

  ojsonstream &print(ojsonstream &ojs) const
  {
    return prt_obj(ojs, KVP(name), KVP(provinces));
  }
};

int main()
{
  ojsonstream ojs(cout.rdbuf());
  ojs << nullptr << endl;
  ojs << string("STL-string") << endl;
  ojs << "C-string" << endl;
  ojs << 1 << endl;
  ojs << 1.0 << endl;
  ojs << true << endl;
  ojs << vector<double>{1.0, 2.0} << endl;
  ojs << map<string, int>{{"a", 1}, {"b", 2}} << endl;
  ojs << Country{
    "中国",
      {
        {"黑龙江", {"哈尔滨", "大庆"}},
        {"广东", {"广州", "深圳", "珠海"}},
        {"台湾", {"台北", "高雄"}},
        {"新疆", {"乌鲁木齐"}},
      }
  } << endl;
}
